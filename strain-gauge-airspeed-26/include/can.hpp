#include "CAN.h"
#include "virtualTimer.h"

class CANInterface {

public:
  void initialize() {
    canBus.Initialize(ICAN::BaudRate::kBaud500K);
  }
  void updateSignals(float n1, float n2, float n3, float n4, float n5, float n6) {
    N1 = n1;
    N2 = n2;
    N3 = n3;
    N4 = n4;
    N5 = n5;
    N6 = n6;

    canBus.Tick();
    timerGroup.Tick(millis());
  }
private: 
  VirtualTimerGroup timerGroup;
  ESPCAN canBus{100U, GPIO_NUM_4, GPIO_NUM_5};

   MakeSignedCANSignal(float, 0, 32, 0.0001, 0) N1 {}; 
   MakeSignedCANSignal(float, 32, 32, 0.0001, 0) N2 {}; 
   CANTXMessage<2> ForceMessage1 {canBus, 0x560, 8, 10, timerGroup, N1, N2};

   MakeSignedCANSignal(float, 0, 32, 0.0001, 0) N3 {}; 
   MakeSignedCANSignal(float, 32, 32, 0.0001, 0) N4 {}; 
   CANTXMessage<2> ForceMessage2 {canBus, 0x561, 8, 10, timerGroup, N3, N4};

   MakeSignedCANSignal(float, 0, 32, 0.0001, 0) N5 {}; 
   MakeSignedCANSignal(float, 32, 32, 0.0001, 0) N6 {}; 
   CANTXMessage<2> ForceMessage3 {canBus, 0x562, 8, 10, timerGroup, N5, N6};

};