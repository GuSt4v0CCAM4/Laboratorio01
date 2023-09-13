#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream inputFile("del_log.txt");
    if (!inputFile) {
        std::cerr << "Error al abrir el archivo de entrada." << std::endl;
        return 1;
    }

    std::string line;
    int lineCount = 0;
    int fileCount = 1;
    std::ofstream outputFile;
    std::ifstream lastLineFile("last_line.txt");

    if (!lastLineFile) {
        std::cerr << "Error al abrir el archivo 'last_line.txt'." << std::endl;
        return 1;
    }

    std::string lastLine;
    std::getline(lastLineFile, lastLine);

    if (!lastLine.empty()) {
        lineCount = std::stoi(lastLine);
        fileCount = lineCount / 5 + 1;
    }

    lastLineFile.close();

    // Leer líneas hasta alcanzar el número de línea almacenado en lineCount
    while (lineCount > 0 && std::getline(inputFile, line)) {
        lineCount--;
    }

    while (std::getline(inputFile, line)) {
        if (lineCount == 0) {
            std::string filename = "0" + std::to_string(fileCount) + ".txt";
            outputFile.open(filename);
            if (!outputFile) {
                std::cerr << "Error al abrir el archivo de salida: " << filename << std::endl;
                return 1;
            }
        }

        outputFile << line << std::endl;
        lineCount++;

        if (lineCount == 5) {
            outputFile.close();
            lineCount = 0;
            fileCount++;
        }
    }

    inputFile.close();

    // Guardar el número de la última línea copiada
    std::ofstream newLastLineFile("last_line.txt");
    if (!newLastLineFile) {
        std::cerr << "Error al abrir el archivo 'last_line.txt' para escritura." << std::endl;
        return 1;
    }
    newLastLineFile << lineCount;
    newLastLineFile.close();

    std::cout << "Se han generado los archivos de salida." << std::endl;

    return 0;
}
