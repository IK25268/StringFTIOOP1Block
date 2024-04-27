#ifndef __String_hpp
#define __String_hpp

class String {
private:
    char* charArr;
    size_t len;
    size_t cap;
    size_t* quantRef;
    void initQuantRef();
    void decrQuantRef();
    void addQuantRef(size_t* _quantRef);
    size_t calcLen(const char* _str) const;
    void fullCopy();
    void calcCapacity(size_t len);
    void calcCapacity();
    void reallocStr(size_t newLen);
public:
    String();
    String(const char* str);
    String(const char* str, size_t n);
    String(size_t n, char c);
    String(const String& str);
    String(const String& str, size_t pos, size_t len = npos);
    virtual ~String();

    size_t size() const;
    size_t capacity() const;
    void reserve(size_t n = 0);
    void clear();
    bool empty() const;

    char& at(size_t pos);
    const char& at(size_t pos) const;

    char& operator[](size_t pos);
    const char& operator[](size_t pos) const;

    char& back();
    const char& back() const;

    char& front();
    const char& front() const;

    String& operator+=(const String& str);
    String& operator+=(const char* str);
    String& operator+=(char c);

    String& operator=(const String& str);
    String& operator=(const char* str);

    //âûïîëíÿåò âñòàâêó ñòðîêè str â ïîçèöèþ pos.
    //Åñëè pos áîëüøå ðàçìåðà ñòðîêè, òî âûáðàñûâàåòñÿ èñêëþ÷åíèå throw std::out_of_range("message");.
    String& insert(size_t pos, const String& str);
    String& insert(size_t pos, const char* str);

    //âûïîëíÿåò óäàëåíèå ïîäñòðîêè â ñòðîêå íà÷èíàÿ ñ ïîçèöèè pos è îõâàòûâàÿ len ñèìâîëîâ.
    //Åñëè len ðàâíÿåòñÿ npos, òî óäàëåíèå ïðîèñõîäèò ñ ïîçèöèè pos äî êîíöà ñòðîêè. Åñëè pos áîëüøå ðàçìåðà ñòðîêè, òî âûáðàñûâàåòñÿ èñêëþ÷åíèå throw    . 
    //std::out_of_range("message");.
    String& erase(size_t pos = 0, size_t len = npos);

    //âûïîëíÿåò çàìåíó ïîäñòðîêè â ñòðîêå íà÷èíàÿ ñ ïîçèöèè pos è îõâàòûâàÿ len ñèìâîëîâ.
    //Åñëè len ðàâíÿåòñÿ npos, òî óäàëåíèå ïðîèñõîäèò ñ ïîçèöèè pos äî êîíöà ñòðîêè.
    //Åñëè pos áîëüøå ðàçìåðà ñòðîêè, òî âûáðàñûâàåòñÿ èñêëþ÷åíèå throw std::out_of_range("message");.
    String& replace(size_t pos, size_t len, const String& str);
    String& replace(size_t pos, size_t len, const char* str);
    String& replace(size_t pos, size_t len, size_t n, char c);

    void swap(String& str);
    const char* data();

    //âîçâðàùàåò èíäåêñ ïîäñòðîêè str (èëè ñèìâîëà c) â ñòðîêå. pos - çàäàåò ïîçèöèþ ñ êîòîðîé íà÷èíàòü ïîèñê.
    //Åñëè ïîäñòðîêó íå íàøëè èëè pos áîëüøå ðàçìåðà ñòðîêè, ìåòîä âîçðàùàåò npos.
    size_t find(const String& str, size_t pos = 0) const;
    size_t find(const char* str, size_t pos = 0) const;
    size_t find(char c, size_t pos = 0) const;

    String substr(size_t pos = 0, size_t len = npos);

    int compare(const String& str) const;
    //ñòàòè÷åñêàÿ êîíñòàíòà ñ ìàêñèìàëüíûì çíà÷åíèåì size_t.
    // Ýòî çíà÷åíèåì ìîæåò áûòü èñïîëüçîâàíî â ìåòîäàõ äëÿ ïàðàìåòðà len, ÷òî îçíà÷àåò "äî êîíöà ñòðîêè".
    //Òàêæå ýòà êîíñòàíòà ìîæåò áûòü èñïîëüçîâàíà â êà÷åñòâå âîçâðàùàåìîãî çíà÷åíèÿ äëÿ óêàçàíèÿ îòñóòñòâèÿ ñîâïàäåíèé.
    static const size_t npos = -1;

    size_t countRef() const;
};

#endif
