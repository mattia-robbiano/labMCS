#include "Vettore.h"
#include "OdeSolver.h"

void OdeSolver::Punto(PuntoMateriale tmp) {
    m_p.push_back(tmp);
}

vector <PuntoMateriale> OdeSolver::Punti() {
    return m_p;
}

PuntoMateriale OdeSolver::Punto(unsigned int i) {
    return m_p[i];
}

unsigned int OdeSolver::N() {
    return m_p.size();
}

void OdeSolver::T(double t0) {
    m_t = t0;
}

double OdeSolver::T() {
    return m_t;
}

void OdeSolver::Passo(double h) {
    m_h = h;
}

double OdeSolver::Passo() {
    return m_h;
}


Vettore OdeSolver::m_eqDiff(unsigned int i, double t, vector <PuntoMateriale> p) {
    //STEP 3 Calcolo dell'accelerazione dovuta a forze interne e forze esterne
    Vettore tmp_sum;
    for (unsigned int j = 0; j != i && j < p.size(); j++) {
        tmp_sum = tmp_sum + fInterna(i, j, t, p);
    }
    tmp_sum = tmp_sum + fEsterna(i, t, p);
    Vettore a = tmp_sum * (1 / p[i].Massa());
    return a;
}

//Da implementare a cura dello studente
void OdeSolver::Cinematica() {

    if (m_method == "Eulero") {
        vector <Vettore> k1(m_p.size());
        vector <Vettore> w1(m_p.size());
        for (unsigned int i = 0; i < m_p.size(); i++) {
            k1[i] = m_h * m_p[i].V();
            w1[i] = m_h * m_eqDiff(i, m_t, m_p);
        }

        for (unsigned int i = 0; i < m_p.size(); i++) {
            m_p[i].R(m_p[i].R() + k1[i]);
            m_p[i].V(m_p[i].V() + w1[i]);
        }

    } else if (m_method == "Rk2") {
        vector <Vettore> k1(m_p.size());
        vector <Vettore> w1(m_p.size());
        for (unsigned int i = 0; i < m_p.size(); i++) {
            k1[i] = m_h * m_p[i].V();
            w1[i] = m_h * m_eqDiff(i, m_t, m_p);
        }
        vector <Vettore> k2(m_p.size());
        vector <Vettore> w2(m_p.size());
        vector <PuntoMateriale> tmp_pm_rk = m_p;
        for (unsigned int i = 0; i < m_p.size(); i++) {
            tmp_pm_rk[i].R(m_p[i].R() + k1[i] * 0.5);
            tmp_pm_rk[i].V(m_p[i].V() + w1[i] * 0.5);
        }
        for (unsigned int i = 0; i < m_p.size(); i++) {
            k2[i] = m_h * tmp_pm_rk[i].V();
            w2[i] = m_h * m_eqDiff(i, m_t + m_h / 2, tmp_pm_rk);
        }
        for (unsigned int i = 0; i < m_p.size(); i++) {
            m_p[i].R(m_p[i].R() + k2[i]);
            m_p[i].V(m_p[i].V() + w2[i]);
        }
    } else if (m_method == "VerletVelocity") {
        vector <Vettore> a_0(m_p.size());
        vector <Vettore> a_1(m_p.size());
        //Aggiorno la posizione (Verlet Position)
        for (unsigned i = 0; i < m_p.size(); ++i) {
            a_0[i] = m_eqDiff(i, m_t, m_p);
            m_p[i].R(m_p[i].R() + m_h * m_p[i].V() + 0.5 * m_h * m_h * a_0[i]);
        }
        //Aggiorno la velocità (Verlet Velocity)
        for (unsigned i = 0; i < m_p.size(); ++i) {
            a_1[i] = m_eqDiff(i, m_t + m_h, m_p);
            m_p[i].V(m_p[i].V() + 0.5 * m_h * (a_1[i] + a_0[i]));
        }
    }
    m_t += m_h;
}


