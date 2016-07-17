#ifndef BACTERIASYSTEM_H
#define BACTERIASYSTEM_H

#include <vector>

class BacteriaSystem
{
public:
    BacteriaSystem(double timeStep_in = 1.0e-2);

    void propagate();

    std::vector<double> getAlimento(){return alimentoNaCelula;}
    std::vector<double> getReagente(){return reagenteNaCelula;}
    std::vector<double> getMetabolito(){ return metabolitoNaCelula; }
    std::vector<double> getResiduo(){ return residuoNaCelula; }
    std::vector<bool> getBacteriaAlive(){ return alive; }

private:
    // celula
    // alimento dentro - reagente dentro - metabolito dentro - residuo dentro
    double constAbsorcao;
    double constReacaoAB;
    double constFormResiduo;
    double constEliminacaoResiduo;
    double porcentagemMaxDeDivisao;
    double maxToxicidade;
    double valorParaReproducao;

    double alimentoFora;
    double residuoFora;

    int nBacterias;
    std::vector<double> alimentoNaCelula;
    std::vector<double> reagenteNaCelula;
    std::vector<double> metabolitoNaCelula;
    std::vector<double> residuoNaCelula;

    std::vector<double> kAbsorcao;
    std::vector<double> kReacaoAB;
    std::vector<double> kFormResiduo;
    std::vector<double> kEliminacaoResiduo;
    std::vector<bool> alive;

    double timeStep;
    double advanceEquations(double dx);
    double randcpp(double fMin, double fMax);
};

#endif // BACTERIASYSTEM_H


// informacao - as primeiras moleculas nao escolheram a camada lipidica por causa
//              das interacoes. mas porque era uma coisa que o separava da agua
//              alem disso era uma coisa que permitia alguns quimicos passarem
//              pra dentro mas deixava outros do lado de fora.
