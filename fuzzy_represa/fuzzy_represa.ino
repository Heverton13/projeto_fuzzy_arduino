#include <Fuzzy.h>
#include <Servo.h>
#define SERVO 6 // Porta Digital 6 (PWM)

Fuzzy *fuzzy = new Fuzzy();

Servo s;
int ldr = A0;
int pot = A5;
int led = 5;
int luminosidade = 0;

void setup() {

  pinMode(led,OUTPUT);
  s.attach(SERVO);
  s.write(0);
  Serial.begin(9600);
  randomSeed(analogRead(0));

  //Conjuntos  de entrada
  FuzzyInput *pressao = new FuzzyInput(1);

  FuzzySet *alta = new FuzzySet(0,100,300,500);
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
  abertura->addFuzzySet(medio);

  FuzzySet * alto = new FuzzySet(90, 135, 180, 180);
  abertura->addFuzzySet(alto);

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
    
    luminosidade = analogRead(pot);
    luminosidade = map(luminosidade,0,1023,0,255);
    analogWrite(led,luminosidade);

    // Passar a luminosidade capitada no ldr como entrada
    int input = analogRead(ldr);
    fuzzy->setInput(1, input);
    
    //Running the Fuzzification
    fuzzy->fuzzify();
    
    // Running the Defuzzification
    int output = fuzzy->defuzzify(1);
    // Result in Servo
    s.write(output);
    
    Serial.print("\t\t\tAbertura: ");
    Serial.println(output);

}
