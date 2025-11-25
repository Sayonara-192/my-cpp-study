#include <iostream>
#include <vector>
#include <iomanip> // For std::setw
#include <fstream> // For file I/O

// ==========================================
// 1. Data Structures (The Blueprints)
// ==========================================

struct Beam {
    int id;
    double angle;
    double depth;
    double intensity;
};

struct SonarPing {
    long long timestamp;
    double ship_heading;
    std::vector<Beam> beams;
};

// ==========================================
// 2. Main Logic
// ==========================================

int main() {
    // --- PART 1: Create and Populate Data in Memory ---
    
    std::cout << "--- [Step 1] Creating Data in Memory ---" << std::endl;
    
    SonarPing currentPing;
    currentPing.timestamp = 1716345600;
    currentPing.ship_heading = 90.5;

    // Add beams (simulating sonar receiving data)
    currentPing.beams.push_back({1, -45.0, 100.5, -20.0});
    currentPing.beams.push_back({2,   0.0,  98.2, -15.5});
    currentPing.beams.push_back({3,  45.0, 100.8, -21.0});
    currentPing.beams.push_back({4,  60.0, 105.0, -22.5}); // The 4th beam

    std::cout << "Created a ping with " << currentPing.beams.size() << " beams." << std::endl;


    // --- PART 2: Serialize and Write to Binary File ---
    
    std::cout << "\n--- [Step 2] Writing to Binary File (Serialization) ---" << std::endl;
    
    FILE* outFile = fopen("data.bin", "wb"); // "wb" = Write Binary

    if (outFile != nullptr) {
        // A. Write Header Info
        fwrite(&currentPing.timestamp, sizeof(long long), 1, outFile);
        fwrite(&currentPing.ship_heading, sizeof(double), 1, outFile);

        // B. Write Vector Size (Crucial!)
        // We must save "how many beams" so the reader knows how many to expect.
        int beamCount = currentPing.beams.size();
        fwrite(&beamCount, sizeof(int), 1, outFile);

        // C. Write Beam Data Loop
        for (const auto& beam : currentPing.beams) {
            fwrite(&beam, sizeof(Beam), 1, outFile);
        }

        fclose(outFile);
        std::cout << "Success: Data saved to 'data.bin'." << std::endl;
    } else {
        std::cout << "Error: Could not open file for writing." << std::endl;
        return 1; // Exit with error code
    }


    // --- PART 3: Verify! Read Back from Binary File ---
    
    std::cout << "\n--- [Step 3] Reading Back from File (Verification) ---" << std::endl;
    
    FILE* inFile = fopen("data.bin", "rb"); // "rb" = Read Binary

    if (inFile != nullptr) {
        // Temp variables to hold read data
        long long readTimestamp;
        double readHeading;
        int readCount;
        std::vector<Beam> readBeams;

        // A. Read Header (Order must match writing!)
        fread(&readTimestamp, sizeof(long long), 1, inFile);
        fread(&readHeading, sizeof(double), 1, inFile);

        // B. Read Count
        fread(&readCount, sizeof(int), 1, inFile);
        
        std::cout << "Header Info -> Time: " << readTimestamp 
                  << ", Heading: " << readHeading 
                  << ", Beams: " << readCount << std::endl;

        // C. Read Beam Data Loop
        for (int i = 0; i < readCount; i++) {
            Beam b;
            // Read one beam struct directly from file
            fread(&b, sizeof(Beam), 1, inFile);
            // Push into our verification vector
            readBeams.push_back(b);
        }

        fclose(inFile);

        // D. Print Result
        std::cout << "\n--- Verifying Beam Data ---" << std::endl;
        for (const auto& b : readBeams) {
            std::cout << "Beam ID: " << b.id 
                      << " | Depth: " << b.depth << "m" 
                      << " | Intensity: " << b.intensity << "dB" 
                      << std::endl;
        }

    } else {
        std::cout << "Error: Could not open file for reading." << std::endl;
    }

    return 0;
}