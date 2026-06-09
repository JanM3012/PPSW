void DetectorInit(void);
enum DetectorState {INACTIVE, ACTIVE};
enum DetectorState eReadDetector(void);
enum ServoState {CALLIB, IDLE, IN_PROGRESS};
void Automat(void);
void ServoInit(unsigned int uiServoFrequency);
void ServoCallib(void);
void ServoGoTo(unsigned int uiPosition);
