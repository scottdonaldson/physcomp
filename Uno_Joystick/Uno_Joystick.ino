
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

}


void loop() {
  // put your main code here, to run repeatedly:
int power = analogRead(A0);
int rotation = analogRead(A1);
power = -power+511;
power=power/5;
rotation=rotation-511;
rotation=rotation/5;

if(abs(power)<3)
{
  power=0;
}
if(abs(rotation)<3)
{
  rotation=0;
}

Serial.print("power: ");
Serial.print(power);
Serial.print(";  ");
Serial.print("rotation: ");
Serial.println(rotation);
}
