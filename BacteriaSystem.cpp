#include "BacteriaSystem.h"

#include <QDebug>
#include <math.h>

BacteriaSystem::BacteriaSystem(double timeStep_in)
{
    timeStep = timeStep_in;
    constAbsorcao = 0.01;
    constReacaoAB = 1;
    constFormResiduo = 1;
    constEliminacaoResiduo = 1;
    porcentagemMaxDeDivisao = 0.5e0;
    maxToxicidade = 50;
    valorParaReproducao = 5;

    //condicoes inicias
    alimentoFora = 100;
    residuoFora = 10;

    alimentoNaCelula.push_back(0);
    reagenteNaCelula.push_back(20);
    metabolitoNaCelula.push_back(0);
    residuoNaCelula.push_back(0);

    kAbsorcao.push_back(constAbsorcao);
    kReacaoAB.push_back(constReacaoAB);
    kFormResiduo.push_back(constFormResiduo);
    kEliminacaoResiduo.push_back(constEliminacaoResiduo);
    alive.push_back(true);

    // constante de toxicidade, explosao e reproducao

}

void BacteriaSystem::propagate()
{
    int k = 0;
    double vAlimentoFora, vAlimento, vReagente, vMetabol, vResiduo, vResiduoFora;
    double alimentoForaTemp;
    double residuoForaTemp;
    do
    {
        for(size_t i = 0; i < alimentoNaCelula.size(); i++)
        {
            alimentoForaTemp = 0.0e0;
            residuoForaTemp = 0.0e0;
            if(alive[i])
            {
                vAlimentoFora = - kAbsorcao[i] * alimentoFora;
                vAlimento = kAbsorcao[i] * alimentoFora - kReacaoAB[i] * alimentoNaCelula[i] * reagenteNaCelula[i];
                vReagente = - kReacaoAB[i] * alimentoNaCelula[i] * reagenteNaCelula[i];
                vMetabol = kReacaoAB[i] * alimentoNaCelula[i] * reagenteNaCelula[i] - kFormResiduo[i] * metabolitoNaCelula[i];
                vResiduo = kFormResiduo[i] * metabolitoNaCelula[i] - kEliminacaoResiduo[i] * residuoNaCelula[i];
                vResiduoFora = kEliminacaoResiduo[i] * residuoNaCelula[i];

                alimentoForaTemp += advanceEquations(vAlimentoFora);
                double newAli = advanceEquations(vAlimento);
                double newRea = advanceEquations(vReagente);
                double newMet = advanceEquations(vMetabol);
                double newRes = advanceEquations(vResiduo);
                residuoForaTemp += advanceEquations(vResiduoFora);

                alimentoNaCelula[i] += newAli;
                reagenteNaCelula[i] += newRea;
                metabolitoNaCelula[i] += newMet;
                residuoNaCelula[i] += newRes;

                if(alimentoNaCelula[i] < 0)
                    alimentoNaCelula[i] = 0;
                if(reagenteNaCelula[i] < 0)
                    reagenteNaCelula[i] = 0;
                if(metabolitoNaCelula[i] < 0)
                    metabolitoNaCelula[i] = 0;
                if(residuoNaCelula[i] < 0)
                    residuoNaCelula[i] = 0;

                qDebug() << "i:  " << i << "  ali:  " << alimentoNaCelula[i] << "  rea:  " << reagenteNaCelula[i]
                      << "  met:  " << metabolitoNaCelula[i] << "  res:  " << residuoNaCelula[i]
                         << " alimentoforatemp:  " << alimentoForaTemp << "  resForatemp  " << residuoForaTemp;
            }
        }
        alimentoFora += alimentoForaTemp;
        residuoFora += residuoForaTemp;
        if(alimentoFora < 0)
            alimentoFora = 0;
        if(residuoFora < 0)
            residuoFora = 0;

        //qDebug() << "fora:  " << alimentoFora << "  res:  " << residuoFora;

        for(size_t i = 0; i < alimentoNaCelula.size() ; i++)
        {
            double totalSpecies = alimentoNaCelula[i] + reagenteNaCelula[i] + metabolitoNaCelula[i] + residuoNaCelula[i];
            if(totalSpecies > maxToxicidade)
                alive[i] = false;
        }

        // testar quem reproduz.


        k++;
    } while(k < 1000);

}

double BacteriaSystem::advanceEquations(double dx)
{
    return timeStep * dx;
}

double BacteriaSystem::randcpp(double fMin, double fMax)
{
    double f = ((double)rand() / (double)(RAND_MAX));
    return fMin + f * (fMax - fMin);
}
