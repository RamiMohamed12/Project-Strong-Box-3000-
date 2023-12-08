void MA1() {
  int l0 = 1;
  int l1 = 1;
  int l2 = 1;
  int t = 1;

  while (l0 == 1) {
    int q1;

    Serial.println("First question: What is the capital City of the United Kingdom?");
    Serial.println("1-London");
    Serial.println("2-Paris");
    Serial.println("3-Bamako");

    while (!Serial.available()) {}
    q1 = Serial.parseInt();
    Serial.flush();  

    if (q1 == 1 ) {
      Serial.println("You are correct, next question.");
      l0 = 0;
    } 
  }

  while (l1 == 1) {
    int q2;

    Serial.println("Spot the impostor here:");
    Serial.println("1-Fish and Chips");
    Serial.println("2-Beans on Toast");
    Serial.println("3-Pasta");
    Serial.println("4-Yorkshire Pudding");

    while (!Serial.available()) {}
    q2 = Serial.parseInt();
    Serial.flush();  

    if (q2 == 3) {
      Serial.println("You are correct, next question.");
      l1 = 0;
    } 
  }

  while (l2 == 1) {
    int q3;

    Serial.println("You wake up on a rainy day in London heading to the MI7 residence. What car are you driving?");
    Serial.println("1-Toyota");
    Serial.println("2-Ford");
    Serial.println("3-Nissan");
    Serial.println("4-Aston Martin");

    while (!Serial.available()) {}
    q3 = Serial.parseInt();
    Serial.flush();  

    if (q3 == 4) {
      Serial.println("You are correct, we can advance to the next stage .");
      l2 = 0;
    } 
  }
  Serial.flush(); 
}

struct Agent {
  char name[2];
  long long int privateKey;
};

Agent agents[] = {
  { "A", 1273 },
  { "B", 103 },
  { "C", 883 },
  { "D", 653 },
  { "E", 467 },
  { "F", 641 },
  { "H", 1321 },
  { "I", 589 },
  { "J", 1039 },
  { "K", 953 },
  { "L", 745 },
  { "M", 919 },
  { "N", 1159 },
  { "O", 713 },
  { "P", 233 },
  { "Q", 1063 }
};

struct PublicKeyAgent {
  char name[2];
  long long int publicKey;
};

PublicKeyAgent publicKeys[] = {
  { "A", 601 },
  { "B", 619 },
  { "C", 631 },
  { "D", 641 },
  { "E", 647 },
  { "F", 653 },
  { "H", 661 },
  { "I", 673 },
  { "J", 691 },
  { "K", 701 },
  { "L", 733 },
  { "M", 739 },
  { "N", 751 },
  { "O", 797 },
  { "P", 809 },
  { "Q", 811 }
};


int codes[16] = {
  1234,  
  5678, 
  9876,  
  4321,  
  1045,  
  7890,  
  6543,  
  2109,  
  1357,  
  8642,  
  5555,  
  9999,  
  1111,  
  8888,  
  7777,  
  2468  
};

char nomsAgents[16][20] = {
  "Agent A",
  "Agent B",
  "Agent C",
  "Agent D",
  "Agent E",
  "Agent F",
  "Agent H",
  "Agent I",
  "Agent J",
  "Agent K",
  "Agent L",
  "Agent M",
  "Agent N",
  "Agent O",
  "Agent P",
  "Agent Q"
};

int code = 0; 

long int p = 61;
long int q = 53;
long int n = p * q;


long int modInverse(long int a, long int m) {
    long int m0 = m;
    long int y = 0, x = 1;

    if (m == 1) {
        return 0;
    }

    while (a > 1) {
        long int q = a / m;
        long int t = m;

        m = a % m, a = t;
        t = y;

        y = x - q * y;
        x = t;
    }

    if (x < 0) {
        x += m0;
    }

    return x;
}

long int customMod(long long int base, long long int exponent, long long int mod) {
    long long int result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exponent /= 2;
    }
    return result;
}

void MA2() {
    char x;
    long long int privateKey = 0;
    long long int publicKey = 0;
    long int e = 0;
    long int p = 61;
    long int q = 53;
    long int phi_n = (p-1) * (q-1);

    Serial.println("Enter agent name:");
    while (Serial.available() == 0) {}
    String input = Serial.readStringUntil('\n');
    x = input.charAt(0);
    
    bool agentFound = false;
    for (int i = 0; i < sizeof(agents) / sizeof(agents[0]); i++) {
        if (x == agents[i].name[0]) {
            privateKey = agents[i].privateKey;
            agentFound = true;
            break;
        }
    }
       if (!agentFound) {
        Serial.println("Invalid agent name. Please enter a valid agent name.");
        Serial.flush();
        exit (0);
    }

    if (!agentFound) {
        Serial.println("Invalid agent name. Please enter a valid agent name.");
        return;
    }
    for (int i = 0; i < sizeof(agents) / sizeof(agents[0]); i++) {
        if (x == agents[i].name[0]) {
            privateKey = agents[i].privateKey;
            break;
        }
    }

    for (int i = 0; i < sizeof(publicKeys) / sizeof(publicKeys[0]); i++) {
        if (x == publicKeys[i].name[0]) {
            publicKey = publicKeys[i].publicKey;
            Serial.println("Insert your public key (e)");
            while (Serial.available() == 0) {}
            e = Serial.parseInt();
            Serial.print("Public key (e) entered: ");
            Serial.println(e);

            if (e != publicKey) {
                Serial.println("Invalid 'e'. Please enter a valid value.");
                Serial.flush();
                exit(0);
            }

            long int m = random(1, 2881);
            long int s = customMod(m, privateKey, n);

            Serial.print("Encoded message: ");
            Serial.println(m);

            Serial.println("Insert your private key (d)");
            while (Serial.available() == 0) {}
            long int d = Serial.parseInt();

         
            if (d != privateKey) {
                Serial.println("Invalid 'd'. Please enter a valid value.");
                Serial.flush();
                exit(0);
            }

            Serial.print("Decoded message:  ");
            long int mp = customMod(s, modInverse(e, phi_n), n);
            Serial.println(mp);

            Serial.print("You are authenticated! Welcome agent ");
            Serial.println(x);
        }
    }
}


void MA3() {
  int l0 = 1;
  int t = 1; 
  while (l0 == 1) {
    int q1;

    Serial.println("Put your eye agent.");
    while (!Serial.available()) {}
    q1 = Serial.parseInt();
    Serial.flush();  

    if (q1 == 1) {
      Serial.println("Your eye scan was successful, you can go to the next stage.");
      l0 = 0;
    }
  }
}

void MA4() {
  int l0 = 1;
  int t = 1; 
  while (l0 == 1) {
    int q1;

    Serial.println("Scanning your hands");
    while (!Serial.available()) {}
    q1 = Serial.parseInt();
    Serial.flush();  

    if (q1 == 1) {
      Serial.println("Your digital scan was successful");
      l0 = 0;
    }
  }
}

void MA5() {
  Serial.println("Entrez votre code :");
  while (Serial.available() <= 0) {
    delay(100);
  }
  code = Serial.parseInt();
  checkCode(code);
}

void checkCode(int enteredCode) {
  bool codeExists = false;
  for (int findCount = 0; findCount < 16; findCount++) {
    if (codes[findCount] == enteredCode) {
      Serial.print("Your code exists, Welcome Agent !  ");
      Serial.println(nomsAgents[findCount]);
      codeExists = true;
      break;
    }
  }
  
  if (!codeExists) {
    Serial.println("Your code doesn't exist");
    Serial.flush();
    exit(0);
  }
}

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(-1);
    randomSeed(analogRead(0)); 
}


void loop()
 {
    MA2();
    MA1(); 
    MA3();
    MA4();
    MA5();
    Serial.flush(); 
    exit(0);
  }
 