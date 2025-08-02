
float
RealDigitFromTextCharacter(char Character)
{
    float Digit = 0.0f;

    if (Character == '1')
    {
        Digit = 1.0f;
    } 
    else if (Character == '2')
    {
        Digit = 2.0f;
    }
    else if (Character == '3')
    {
        Digit = 3.0f;
    }
    else if (Character == '4')
    {
        Digit = 4.0f;
    }
    else if (Character == '5')
    {
        Digit = 5.0f;
    }
    else if (Character == '6')
    {
        Digit = 6.0f;
    }
    else if (Character == '7')
    {
        Digit = 7.0f;
    }
    else if (Character == '8')
    {
        Digit = 8.0f;
    }
    else if (Character == '9')
    {
        Digit = 9.0f;
    }

    return Digit;
}

uint32_t
UnsignedDigitFromTextCharacter(char Character)
{
    uint32_t Digit = 0;

    if(Character == '1')
    {
         Digit = 1;
    } 
    else if (Character == '2')
    {
         Digit = 2;
    }
    else if (Character == '3')
    {
         Digit = 3;
    }
    else if (Character == '4')
    {
         Digit = 4;
    }
    else if (Character == '5')
    {
         Digit = 5;
    }
    else if (Character == '6')
    {
         Digit = 6;
    }
    else if (Character == '7')
    {
         Digit = 7;
    }
    else if (Character == '8')
    {
         Digit = 8;
    }
    else if (Character == '9')
    {
         Digit = 9;
    }

    return Digit;
}

struct obj_scan_result
{
    float Value;
    char *AdvancedScan;
};

// NOTE: (Ted)  This function gets the scan pointer to the character
//              right after the floating point value. It effectively
//              "consumes" the floating point value.
obj_scan_result
ConstructFloatFromScan(char *Scan, uint32_t SignificantDigits)
{
    obj_scan_result Result = {};
    float VertexValue = 0.0f;

    char First = *Scan++;
    int32_t IsNegative = false;

    float TensDigit = 0.0f;

    if (First == '-')
    {
        IsNegative = true;

        char TensPlace = *Scan++;
        TensDigit = RealDigitFromTextCharacter(TensPlace);
    } else
    {
        TensDigit = RealDigitFromTextCharacter(First);
    }

    VertexValue += TensDigit;

    Scan++;
    char TenthsPlace = *Scan++;
    float TenthsDigit = RealDigitFromTextCharacter(TenthsPlace);
    VertexValue += TenthsDigit*0.1f;

    char HundredthsPlace = *Scan++;
    float HundredthsDigit = RealDigitFromTextCharacter(HundredthsPlace);
    VertexValue += HundredthsDigit*0.01f;

    char ThousandthsPlace = *Scan++;
    float ThousandthsDigit = RealDigitFromTextCharacter(ThousandthsPlace);
    VertexValue += ThousandthsDigit*0.001f;

    char TenThousandthsPlace = *Scan++;
    float TenThousandthsDigit = RealDigitFromTextCharacter(TenThousandthsPlace);
    VertexValue += TenThousandthsDigit*0.0001f;

    if (SignificantDigits > 4)
    {
        char HundredThousandthsPlace = *Scan++;
        float HundredThousandthsDigit = RealDigitFromTextCharacter(HundredThousandthsPlace);
        VertexValue += HundredThousandthsDigit*0.00001f;

        char MillionthsPlace = *Scan++;
        float MillionthsDigit = RealDigitFromTextCharacter(MillionthsPlace);
        VertexValue += MillionthsDigit*0.000001f;
    }

    if (IsNegative)
    {
        VertexValue *= -1;
    }

    // TODO: (Ted)  This should be "agnostic" about what happens outside of it and shouldn't
    //              try to move the scan pointer to the next value itself. Calling code should
    //              have that responsibility.
    
    // Do this to get to the next value.
    //Scan++;

    Result.Value = VertexValue;
    Result.AdvancedScan = Scan;

    return (Result);
}

char*
ScanToLineStartingWithCharacter(char StartCharacter, char *Scan, char *Line)
{
    int32_t Scanning = true;

#if WINDOWS
    char NewLineToken = '\r';
    uint32_t CharactersToNextLineAfterNewLineToken = 2;
#elif MACOS
    char NewLineToken = '\n';
    uint32_t CharactersToNextLineAfterNewLineToken = 1;
#endif

    while(Scanning)
    {
        if (*Line == StartCharacter)
        {
            Scanning = false;
        } else
        {
            // NOTE: (Ted)  Skip Lines
            while(true)
            {
                if(*Scan == NewLineToken)
                {
                    break;
                }

                Scan++;
            }

            Scan += CharactersToNextLineAfterNewLineToken;
            Line = Scan;
            continue;
        }
    }

    return Scan;
}

uint32_t
GetFaceLookupIndexFromCharacters(char *Characters, uint32_t CharacterCount)
{
    uint32_t FaceLookupIndex = 0;
    uint32_t OnesDigit = 0;
    uint32_t TensDigit = 0;
    uint32_t HundredsDigit = 0;
    uint32_t ThousandsDigit = 0;

    if(CharacterCount == 1)
    {
        char DigitCharacter = Characters[0];
        OnesDigit = UnsignedDigitFromTextCharacter(DigitCharacter);
    } else if (CharacterCount == 2)
    {
        char TensDigitCharacter = Characters[0];
        char OnesDigitCharacter = Characters[1];
        TensDigit = UnsignedDigitFromTextCharacter(TensDigitCharacter);
        OnesDigit = UnsignedDigitFromTextCharacter(OnesDigitCharacter);
    } else if (CharacterCount == 3)
    {
        char HundredsDigitCharacter = Characters[0];
        char TensDigitCharacter = Characters[1];
        char OnesDigitCharacter = Characters[2];
        HundredsDigit = UnsignedDigitFromTextCharacter(HundredsDigitCharacter);
        TensDigit = UnsignedDigitFromTextCharacter(TensDigitCharacter);
        OnesDigit = UnsignedDigitFromTextCharacter(OnesDigitCharacter);
    } else if (CharacterCount == 4)
    {
        char ThousandsDigitCharacter = Characters[0];
        char HundredsDigitCharacter = Characters[1];
        char TensDigitCharacter = Characters[2];
        char OnesDigitCharacter = Characters[3];
        ThousandsDigit = UnsignedDigitFromTextCharacter(ThousandsDigitCharacter);
        HundredsDigit = UnsignedDigitFromTextCharacter(HundredsDigitCharacter);
        TensDigit = UnsignedDigitFromTextCharacter(TensDigitCharacter);
        OnesDigit = UnsignedDigitFromTextCharacter(OnesDigitCharacter);
    }
     
    FaceLookupIndex = OnesDigit + 10*TensDigit + 100*HundredsDigit + 1000*ThousandsDigit - 1;

    return (FaceLookupIndex);
}

struct obj_face_scan
{
    uint32_t CharacterCount;
    char Characters[4];
    char *AdvancedScan;
};

obj_face_scan
GetFaceCharactersUpToToken(char *Scan, char Token)
{
    obj_face_scan Result = {};
    uint32_t CharacterCount = 0;

    while(*Scan != Token)
    {
        Result.Characters[CharacterCount] = *Scan;
        CharacterCount++;
        Scan++;
    }

    Scan++;

    Result.CharacterCount = CharacterCount;
    Result.AdvancedScan = Scan;
    return (Result);
}
