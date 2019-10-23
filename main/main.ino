#include <Wire.h>

// Define O Endereco Do HMC5883 - 0x1E Ou 30 Em Decimal
#define Address 0x1E 

typedef struct Coord
{
	int x = 0, y = 0, z = 0;
} coordinates;

void setup()
{
	Serial.begin(9600);
	Wire.begin();
	
	// Inicializa O HMC5883
	Wire.beginTransmission(Address);
	// Seleciona O Modo
	Wire.write(0x02); 
	// Modo De Medicao Continuo
	Wire.write(0x00); 
	Wire.endTransmission();
}

void loop()
{
	coordinates north, compassGPS, rocketGPS;	//Triple Axis Data
	coordinates rocketCompassVector;

	//~~~~ Receive GPS location of the rocket ~~~~
	//~~~~ Get compass location via GPS ~~~~
	
	// Indica Ao HMC5883 Para Iniciar A Leitura
	Wire.beginTransmission(Address);
	Wire.write(0x03); //Select Register 3, X MSB Register
	Wire.endTransmission();
	 
	// Le Os Dados De Cada Eixo, 2 Registradores Por Eixo
	Wire.requestFrom(Address, 6);
	if(6<=Wire.available())
	{
		north.x = Wire.read()<<8;	//X Msb
		north.x |= Wire.read();		//X Lsb
		north.y = Wire.read()<<8;	//Z Msb
		north.y |= Wire.read();		//Z Lsb
		north.z = Wire.read()<<8;	//Y Msb
		north.z |= Wire.read();		//Y Lsb
	}

	// Get the vector relative to the line between rocket and compass

	int dotProduct = north.x * rocketCompassVector.x + north.y * rocketCompassVector.y;
	int northNorm = sqrt(sq(north.x) + sq(north.y));
	int rocketCompassNorm = sqrt(sq(rocketCompassVector.x) + sq(rocketCompassVector.y));
	int angle = acos(dotProduct/(northNorm*rocketCompassNorm));

	Serial.print("angle: ");
	Serial.println(angle);

	// Switch case to light up LEDs
	
}


/*
notes:
	It may be better to just work with the x and y axis and ignore the z axis entirely
	But I don't know the implications in the order of data received by "Wire.read()"

	Check if we can use floats
*/
