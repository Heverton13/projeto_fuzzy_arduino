#include <Fuzzy.h>

Fuzzy = *fuzzy = new Fuzzy();
int ldr = A0;
int led = 5;

void setup() {

  pinMode(led,OUTPUT);
  Serial.begin(9600);

  //Conjuntos  de entrada
  FuzzyInput *pressao = new FuzzyInput(1);

  FuzzySet *alta = new FuzzySet(0,0,300,500);
  pressao -> addFuzzySet(alta);

  FuzzySet *media = new FuzzySet(300,500,700,800);
  pressao -> addFuzzySet(media);

  FuzzySet *baixa = new FuzzySet(700,800,1023,1023);
  pressao -> addFuzzySet(baixa);

  fuzzy -> addFuzzyInput(pressao);

  //Conjuntos de saída

  FuzzyOutput *abertura = new FuzzyOutput(1);

  FuzzySet * pequena = new FuzzySet(0, 45, 45, 90);
  abertura->addFuzzySet(pequena);
  
  FuzzySet * media = new FuzzySet(45, 90, 90, 135);
  abertura->addFuzzySet(pequena);

  FuzzySet * alta = new FuzzySet(90, 135, 135, 180);
  abertura->addFuzzySet(alta);

  fuzzy->addFuzzyOutput(abertura);

  //Regras 
  
  FuzzyRuleAntecedent *ifPressaoBaixa = new FuzzyRuleAntecedent();
  
  ifPressaoBaixa->joinSingle(baixa);
  
  FuzzyRuleConsequent *thenAberturaPequena = new FuzzyRuleConsequent();
  
  thenAnguloBaixo->addOutput(pequena);
 
  FuzzyRule *fuzzyRule01 = new FuzzyRule(1,  ifPressaoBaixa, thenAnguloBaixo);
 
  fuzzy->addFuzzyRule(fuzzyRule01);

  // Fazer Regras 2 - Media

  // Fazer regra 3 - Alta

}

void loop() {
  // Realizar Operações

}
