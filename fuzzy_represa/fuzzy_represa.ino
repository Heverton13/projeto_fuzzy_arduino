#include <Fuzzy.h>

Fuzzy *fuzzy = new Fuzzy();
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
  
  FuzzySet * medio = new FuzzySet(45, 90, 90, 135);
  abertura->addFuzzySet(pequena);

  FuzzySet * alto = new FuzzySet(90, 135, 135, 180);
  abertura->addFuzzySet(alta);

  fuzzy->addFuzzyOutput(abertura);

  //Regras 
  
  FuzzyRuleAntecedent *ifPressaoBaixa = new FuzzyRuleAntecedent();
  
  ifPressaoBaixa->joinSingle(baixa);
  
  FuzzyRuleConsequent * thenAnguloBaixo = new FuzzyRuleConsequent();
  
  thenAnguloBaixo -> addOutput(pequena);
 
  FuzzyRule *fuzzyRule01 = new FuzzyRule(1,  ifPressaoBaixa, thenAnguloBaixo);
 
  fuzzy->addFuzzyRule(fuzzyRule01);

  // Fazer Regras 2 - Media
  FuzzyRuleAntecedent *ifPressaoMedia = new FuzzyRuleAntecedent();
  
  ifPressaoMedia->joinSingle(media);
  
  FuzzyRuleConsequent *thenAnguloMedio = new FuzzyRuleConsequent();
  
  thenAnguloMedio->addOutput(medio);
  
  FuzzyRule *fuzzyRule02 = new FuzzyRule(2, ifPressaoMedia, thenAnguloMedio);
  
  fuzzy->addFuzzyRule(fuzzyRule02);

  // Fazer regra 3 - Alta
  FuzzyRuleAntecedent *ifPressaoAlta = new FuzzyRuleAntecedent();
  
  ifPressaoAlta->joinSingle(alta);
  
  FuzzyRuleConsequent *thenAnguloAlto = new FuzzyRuleConsequent();
 
  thenAnguloAlto->addOutput(alto);
  
  FuzzyRule *fuzzyRule03 = new FuzzyRule(3, ifPressaoAlta, thenAnguloAlto);
  
  fuzzy->addFuzzyRule(fuzzyRule03);

}

void loop() {
  // Realizar Operações

    // Teste com variáveis aleatórias
     int input = random(0, 1023);
    // Printing something
    Serial.println("\n\n\nEntrance: ");
    Serial.print("\t\t\tPressao: ");
    Serial.println(input);
    // Set the random value as an input
    fuzzy->setInput(1, input);
    // Running the Fuzzification
    fuzzy->fuzzify();
    // Running the Defuzzification
    float output = fuzzy->defuzzify(1);
    // Printing something
    Serial.println("Result: ");
    Serial.print("\t\t\tAbertura: ");
    Serial.println(output);
    // wait 12 seconds
    delay(12000);

}
