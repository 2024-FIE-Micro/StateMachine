#include <Arduino.h>


class IState
{
public:
  IState ()
  {
  }
  virtual void input_1 (IState ** ptr_ptr, IState * availableStates[], int &var) = 0;
  virtual void input_0 (IState ** ptr_ptr, IState * availableStates[], int &var) = 0;
  void print(String state, int input, String func, String newState, int acum) { 
    Serial.print("from state: ");
    Serial.print(state);
    Serial.print("; input: ");
    Serial.print(input);
    Serial.print("; function: ");
    Serial.print(func);
    Serial.print("; to state: ");
    Serial.print(newState);
    Serial.print("; acum= ");
    Serial.println(acum);
  }
};

class StateA:public IState
{
public:
  StateA ()
  {
  }
  void input_1 (IState ** ptr_ptr, IState * availableStates[], int &var)
  {
    var = var - 1;
    this->print("A", 1, "aa", "B", var);
    *ptr_ptr = (availableStates[1]); //Transicion
  }
  void input_0 (IState ** ptr_ptr, IState * availableStates[], int &var)
  {
    this->print("A", 0, "nothing", "A", var);
  }
};

class StateB:public IState
{
public:
  StateB ()
  {
  }
  void input_1 (IState ** ptr_ptr, IState * availableStates[], int &var)
  {
    this->print("B", 1, "nothing", "B", var);
  }
  void input_0 (IState ** ptr_ptr, IState * availableStates[], int &var)
  {
    var = var + 0;
    this->print("B", 0, "bb", "A", var);
    *ptr_ptr = availableStates[0]; //Transicion
  }
};

StateA stateA;
StateB stateB;
IState *state_array[2] = { &stateA, &stateB };
IState *ptr = &stateA;

int inputValues[] = {1, 0, 1, 0, 0, 0, 1, 1}; // Simulated input values
int acum = 0;

void (IState::*transitions[2])(IState ** ptr_ptr, IState* availableStates[], int &var) = {
  &IState::input_0,
  &IState::input_1
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // ptr->input_1 (&ptr, state_array, 1);
  // ptr->input_1 (&ptr, state_array, 1);
  // ptr->input_0 (&ptr, state_array, 1);
  // ptr->input_0 (&ptr, state_array, 1);

  for (unsigned int i = 0; i < sizeof(inputValues) / sizeof(inputValues[0]); i++) {
    int input = inputValues[i];
    (ptr->*transitions[input - 1])(&ptr, state_array, acum);
  }
}
