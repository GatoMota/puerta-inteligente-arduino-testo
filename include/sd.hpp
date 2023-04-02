#include "../include/ArduinoJson-v6.21.1.h"

// Constructor
void startSD() {
    if (!SD.begin(SDPIN))
    {
        Serial.println("No se pudo inicializar");
        return;
    }
    Serial.println("inicializacion exitosa");
}
// Check if file already exists in SD
bool checkFileExists(String filename) {
    if (SD.exists(filename)) {
        return true;
    }
    else {
        return false;
    }
}
// Find or create
void findOrCreateSD() {
    String filename = "exDev.txt";
    if (checkFileExists(filename)) {
        exDevFile = SD.open(filename);
    }
    else
    {
        boolean created = SD.mkdir(filename);
        if (created)
        {
            exDevFile = SD.open(filename);
        }
        else
        {
            Serial.println("No se pudo crear el archivo");
        }
    }
}
// Write
void writeSD(String text)
{
    findOrCreateSD();
    if (exDevFile)
    {
        exDevFile.println(text);
        exDevFile.close();
    }
}
// Find in file
bool findSD(String id)
{
    findOrCreateSD();
    if (exDevFile) {
        // The filter: it contains "true" for each value we want to keep
        StaticJsonDocument<200> filter;
        filter["miembros"][0]["id"] = id;
        // Deserialize the document
        StaticJsonDocument<400> doc;
        deserializeJson(doc, exDevFile, DeserializationOption::Filter(filter));

        // Print the result
        serializeJsonPretty(doc, Serial);
        //String nombre = serializeJsonPretty(doc, Serial);

    }
    return false;
}