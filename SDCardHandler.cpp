// 
// 
// 

#include "SDCardHandler.h"

void SDCardHandlerClass::BeginSD() {

	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB port only
	}
	Serial.print("Initializing SD card...");

	bool contected = false;
	do
	{
		if (!SD.begin(53)) {
			Serial.println("initialization failed!");
			
		}
		else
		{
			Serial.println("initialization done.");
			contected = true;

		}

	} while (!contected);

}

size_t SDCardHandlerClass::readField(File * file, char * str, size_t size, char * delim)
{
	char ch;
	size_t n = 0;
	while ((n + 1) < size && file->read(&ch, 1) == 1) {
		// Delete CR.
		if (ch == '\r') {
			continue;
		}
		str[n++] = ch;
		if (strchr(delim, ch)) {
			break;
		}
	}
	str[n] = '\0';
	return n;
}

bool SDCardHandlerClass::Save(Container oldBottles[6])
{

	if (SD.exists("test.txt")) {
		Serial.println("File exists.");
		SD.remove("test.txt");
	}
	else {
		Serial.println("test.txt doesn't exist.");
		return false;
	}

	myFile = SD.open("test.txt", FILE_WRITE);


	// open the file. note that only one file can be open at a time,
	// so you have to close this one before opening another.

	// if the file opened okay, write to it:

	if (myFile) {


		String dataToSave = "";
		int pos = 0;
		for (size_t i = 0; i < 6; i++)
		{

			Serial.print("Writing: \nName:");

			dataToSave += oldBottles[i].GetName();
			Serial.print(oldBottles[i].GetName());

			dataToSave += ",";
			Serial.print(",");

			dataToSave += oldBottles[i].GetAmount();
			Serial.print(oldBottles[i].GetAmount());

			dataToSave += "\n";
			Serial.println("\\n");

		}
		myFile.print(dataToSave);

		Serial.print("Writing: 1;Name;5123;");

		// close the file:
		myFile.close();

		Serial.println("\nDone saving");

	}
	else {
		// if the file didn't open, print an error:
		Serial.println("error opening test.txt");
	}

	return true;
}

void SDCardHandlerClass::Load(Container *containers)
{
	/////
	///// Reading
	///// 

	myFile = SD.open("test.txt");
	String savedData;
	if (myFile) {
		Serial.println("opened test.txt:");
	}
	else {
		// if the file didn't open, print an error:
		Serial.println("error opening test.txt");
	}





	Serial.println("\n\nLoading from SD");

	/////
	///// Cutting
	/////

	size_t n;      // Length of returned field with delimiter.
	char str[30];  // Must hold longest field with delimiter and zero byte.

				   // Read the file and print fields.
	int pos = 0;
	while (true) {
		n = readField(&myFile, str, sizeof(str), ",\n");

		// done if Error or at EOF.
		if (n == 0) break;

		// Print the type of delimiter.
		if (str[n - 1] == ',' || str[n - 1] == '\n') {
			Serial.print(str[n - 1] == ',' ? F("Name:   ") : F("Amount: "));
			

			if (str[n - 1] == ',')
			{
				//st = myString.substr(0, myString.size() - 1);
				// Trimmed string
				String st;
				st = String(str);
				st = st.substring(0, st.length() - 1);

				containers[pos].SetName(st);
				Serial.println(containers[pos].GetName());
			}
			else if (str[n - 1] == '\n')
			{
				String number = str;
				containers[pos].SetAmount(number.toInt());
				Serial.println(containers[pos].GetAmount());
				pos++;
			}
				if (pos >= 6)
				{
					break;
				}
			// Remove the delimiter.
			continue;
		}
		else {
			// At eof, too long, or read error.  Too long is error.
			Serial.print(myFile.available() ? "error: " : "eof:   ");
		}
		// Print the field.
		Serial.print("Couldn't parse and load: ");
		Serial.println(str);
	}

	myFile.close();

	Serial.println("------------\nDone loading");

}

SDCardHandlerClass SDCardHandler;

