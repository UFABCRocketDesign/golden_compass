// Programa : Teste HMC5883L - Bussola
// Adaptacoes : Arduino E Cia

#Include <Wire.h>

// Define O Endereco Do HMC5883 - 0x1E Ou 30 Em Decimal
#Define Address 0x1E 

Void Setup()
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

Void Loop()
{
	Int X,Y,Z; //Triple Axis Data
	
	// Indica Ao HMC5883 Para Iniciar A Leitura
	Wire.beginTransmission(Address);
	Wire.write(0x03); //Select Register 3, X MSB Register
	Wire.endTransmission();
 
	// Le Os Dados De Cada Eixo, 2 Registradores Por Eixo
	Wire.requestFrom(Address, 6);
	If(6<=Wire.available())
	{
		X = Wire.read()<<8; //X Msb
		X |= Wire.read(); //X Lsb
		Z = Wire.read()<<8; //Z Msb
		Z |= Wire.read(); //Z Lsb
		Y = Wire.read()<<8; //Y Msb
		Y |= Wire.read(); //Y Lsb
	}
	
	// Imprime Os Vaores No Serial Monitor
	Serial.print("X: ");
	Serial.print(X);
	Serial.print("	Y: ");
	Serial.print(Y);
	Serial.print("	Z: ");
	Serial.println(Z);
	
	Delay(250);
}
