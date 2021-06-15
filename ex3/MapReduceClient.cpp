

//// THIS IS THE SAMPLE CLIENT
//#include "MapReduceClient.h"
//#include "MapReduceFramework.h"
//#include <cstdio>
//#include <string>
//#include <array>
//#include <unistd.h>
//
//class VString : public V1 {
//public:
//    VString(std::string content) : content(content) { }
//    std::string content;
//};
//
//class KChar : public K2, public K3{
//public:
//    KChar(char c) : c(c) { }
//    virtual bool operator<(const K2 &other) const {
//        return c < static_cast<const KChar&>(other).c;
//    }
//    virtual bool operator<(const K3 &other) const {
//        return c < static_cast<const KChar&>(other).c;
//    }
//    char c;
//};
//
//class VCount : public V2, public V3{
//public:
//    VCount(int count) : count(count) { }
//    int count;
//};
//
//
//class CounterClient : public MapReduceClient {
//public:
//    void map(const K1* key, const V1* value, void* context) const {
//        std::array<int, 256> counts;
//        counts.fill(0);
//        for(const char& c : static_cast<const VString*>(value)->content) {
//            counts[(unsigned char) c]++;
//        }
//
//        for (int i = 0; i < 256; ++i) {
//            if (counts[i] == 0)
//                continue;
//            KChar* k2 = new KChar(i);
//            VCount* v2 = new VCount(counts[i]);
//            usleep(150000);
//            emit2(k2, v2, context);
//        }
//    }
//
//    virtual void reduce(const IntermediateVec* pairs,
//                        void* context) const {
//        const char c = static_cast<const KChar*>(pairs->at(0).first)->c;
//        int count = 0;
//        for(const IntermediatePair& pair: *pairs) {
//            count += static_cast<const VCount*>(pair.second)->count;
//            delete pair.first;
//            delete pair.second;
//        }
//        KChar* k3 = new KChar(c);
//        VCount* v3 = new VCount(count);
//        usleep(150000);
//        emit3(k3, v3, context);
//    }
//};
//
//
//int main(int argc, char** argv)
//{
//    CounterClient client;
//    InputVec inputVec;
//    OutputVec outputVec;
//    VString s1("This string is full of characters");
//    VString s2("Multithreading is awesome");
//    VString s3("race conditions are bad");
//
//    inputVec.push_back({nullptr, &s1});
//    inputVec.push_back({nullptr, &s2});
//    inputVec.push_back({nullptr, &s3});
//
//    JobState state;
//    JobState last_state={UNDEFINED_STAGE,0};
//    JobHandle job = startMapReduceJob(client, inputVec, outputVec, 22);
//    getJobState(job, &state);
//
//    while (state.stage != REDUCE_STAGE || state.percentage != 100.0)
//    {
//        if (last_state.stage != state.stage || last_state.percentage != state.percentage){
//            printf("stage %d, %f%% \n",
//                   state.stage, state.percentage);
//        }
//        usleep(100000);
//        last_state = state;
//        getJobState(job, &state);
//    }
//    printf("stage %d, %f%% \n",
//           state.stage, state.percentage);
//    printf("Done!\n");
//
//    closeJobHandle(job);
//
//    printf("Num of tuples: %lu\n", outputVec.size());
//
//    for (OutputPair& pair: outputVec) {
//        char c = ((const KChar*)pair.first)->c;
//        int count = ((const VCount*)pair.second)->count;
//        printf("The character %c appeared %d time%s\n",
//               c, count, count > 1 ? "s" : "");
//        delete pair.first;
//        delete pair.second;
//    }
//
//    return 0;
//}





//// Little Client
///**
// *
// * @author: Hadas Jacobi, 2018.
// *
// * This client maps 14 ints to even or odd and sums both groups separately.
// *
// */
//
//#include "MapReduceFramework.h"
//#include <cstdio>
//#include <iostream>
//#include <zconf.h>
//
//class Vint : public V1 {
//public:
//    explicit Vint(int content) : content(content) { }
//    int content;
//};
//
//class Kbool : public K2, public K3{
//public:
//    explicit Kbool(bool i) : key(i) { }
//    virtual bool operator<(const K2 &other) const {
//        return key < static_cast<const Kbool&>(other).key;
//    }
//    virtual bool operator<(const K3 &other) const {
//        return key < static_cast<const Kbool&>(other).key;
//    }
//    bool key;
//};
//
//class Vsum : public V2, public V3{
//public:
//    explicit Vsum(int sum) : sum(sum) { }
//    int sum;
//};
//
//
//class modsumClient : public MapReduceClient {
//public:
//    // maps to even or odd
//    void map(const K1* key, const V1* value, void* context) const {
//        int c = static_cast<const Vint*>(value)->content;
//        Kbool* k2;
//        Vsum* v2 = new Vsum(c);
//
//        if(c % 2 == 0){
//            k2 = new Kbool(0);
//        } else {
//            k2 = new Kbool(1);
//        }
//        emit2(k2, v2, context);
//    }
//
//    // sums all evens and all odds
//    virtual void reduce(const IntermediateVec* pairs, void* context) const {
//        const bool key = static_cast<const Kbool*>(pairs->at(0).first)->key;
//        int sum = 0;
//        for(const IntermediatePair& pair: *pairs) {
//            sum += static_cast<const Vsum*>(pair.second)->sum;
//            delete pair.first;
//            delete pair.second;
//        }
//        Kbool* k3 = new Kbool(key);
//        Vsum* v3 = new Vsum(sum);
//        emit3(k3, v3, context);
//    }
//};
//
//
//int main(int argc, char** argv)
//{
//    modsumClient client;
//    InputVec inputVec;
//    OutputVec outputVec;
//
//    Vint s1(86532);
//    Vint s2(657);
//    Vint s3(5);
//    Vint s4(546);
//    Vint s5(54);
//    Vint s6(7);
//    Vint s7(8888);
//    Vint s8(86532);
//    Vint s9(657);
//    Vint s10(5);
//    Vint s11(546);
//    Vint s12(54);
//    Vint s13(7);
//    Vint s14(8888);
//
//
//
//
//
//// Little Client
///**
// *
// * @author: Hadas Jacobi, 2018.
// *
// * This client maps 14 ints to even or odd and sums both groups separately.
// *
// */
//
//#include "MapReduceFramework.h"
//#include <cstdio>
//#include <iostream>
//#include <zconf.h>
//
//class Vint : public V1 {
//public:
//    explicit Vint(int content) : content(content) { }
//    int content;
//};
//
//class Kbool : public K2, public K3{
//public:
//    explicit Kbool(bool i) : key(i) { }
//    virtual bool operator<(const K2 &other) const {
//        return key < static_cast<const Kbool&>(other).key;
//    }
//    virtual bool operator<(const K3 &other) const {
//        return key < static_cast<const Kbool&>(other).key;
//    }
//    bool key;
//};
//
//class Vsum : public V2, public V3{
//public:
//    explicit Vsum(int sum) : sum(sum) { }
//    int sum;
//};
//
//
//class modsumClient : public MapReduceClient {
//public:
//    // maps to even or odd
//    void map(const K1* key, const V1* value, void* context) const {
//        int c = static_cast<const Vint*>(value)->content;
//        Kbool* k2;
//        Vsum* v2 = new Vsum(c);
//
//        if(c % 2 == 0){
//            k2 = new Kbool(0);
//        } else {
//            k2 = new Kbool(1);
//        }
//        emit2(k2, v2, context);
//    }
//
//    // sums all evens and all odds
//    virtual void reduce(const IntermediateVec* pairs, void* context) const {
//        const bool key = static_cast<const Kbool*>(pairs->at(0).first)->key;
//        int sum = 0;
//        for(const IntermediatePair& pair: *pairs) {
//            sum += static_cast<const Vsum*>(pair.second)->sum;
//            delete pair.first;
//            delete pair.second;
//        }
//        Kbool* k3 = new Kbool(key);
//        Vsum* v3 = new Vsum(sum);
//        emit3(k3, v3, context);
//    }
//};
//
//
//int main(int argc, char** argv)
//{
//    modsumClient client;
//    InputVec inputVec;
//    OutputVec outputVec;
//
//    Vint s1(86532);
//    Vint s2(657);
//    Vint s3(5);
//    Vint s4(546);
//    Vint s5(54);
//    Vint s6(7);
//    Vint s7(8888);
//    Vint s8(86532);
//    Vint s9(657);
//    Vint s10(5);
//    Vint s11(546);
//    Vint s12(54);
//    Vint s13(7);
//    Vint s14(8888);
//
//    inputVec.push_back({nullptr, &s1});
//    inputVec.push_back({nullptr, &s2});
//    inputVec.push_back({nullptr, &s3});
//    inputVec.push_back({nullptr, &s4});
//    inputVec.push_back({nullptr, &s5});
//    inputVec.push_back({nullptr, &s6});
//    inputVec.push_back({nullptr, &s7});
//    inputVec.push_back({nullptr, &s8});
//    inputVec.push_back({nullptr, &s9});
//    inputVec.push_back({nullptr, &s10});
//    inputVec.push_back({nullptr, &s11});
//    inputVec.push_back({nullptr, &s12});
//    inputVec.push_back({nullptr, &s13});
//    inputVec.push_back({nullptr, &s14});
//
//    JobState state;
//    JobState last_state={UNDEFINED_STAGE,0};
//    JobHandle job = startMapReduceJob(client, inputVec, outputVec, 5);
//    getJobState(job, &state);
//
//    while (state.stage != REDUCE_STAGE || state.percentage != 100.0)
//    {
//        if (last_state.stage != state.stage || last_state.percentage != state.percentage){
//            printf("stage %d, %f%% \n",
//                   state.stage, state.percentage);
//        }
//        usleep(0);
//        last_state = state;
//        getJobState(job, &state);
//    }
//    printf("stage %d, %f%% \n",
//           state.stage, state.percentage);
//    printf("Done!\n");
//
//    closeJobHandle(job);
//
//
//    for (OutputPair& pair: outputVec) {
//        bool key = ((const Kbool*)pair.first)->key;
//        int sum = ((const Vsum*)pair.second)->sum;
//        printf("The sum of numbers where mod2 == %d is %d\n", key, sum);
//        delete pair.first;
//        delete pair.second;
//    }
//
//    return 0;
//}






////big client:
///**
// * @author: Hadas Jacobi, 2018.
// *
// * This client generates 500,000 random ints in the range 0-5000.
// * It then divides them into groups according to their modulo 1000, and sums each group separately.
// *
// */
//
//#include "MapReduceFramework.h"
//#include <cstdio>
//#include <cstdlib>
//
//#define MOD 1000
//#define INPUTS 500000  // Can't make it any larger or I get a segfault
//
//class Vint : public V1 {
//public:
//    Vint() {}
//    explicit Vint(int content) : content(content) { }
//    int content;
//};
//
//class Kint : public K2, public K3{
//public:
//    explicit Kint(int i) : key(i) { }
//    virtual bool operator<(const K2 &other) const {
//        return key < static_cast<const Kint&>(other).key;
//    }
//    virtual bool operator<(const K3 &other) const {
//        return key < static_cast<const Kint&>(other).key;
//    }
//    int key;
//};
//
//class Vsum : public V2, public V3{
//public:
//    explicit Vsum(ulong sum) : sum(sum) { }
//    ulong sum;
//};
//
//
//class modsumClient : public MapReduceClient {
//public:
//    // maps to modulo MOD
//    void map(const K1* key, const V1* value, void* context) const {
//        int c = static_cast<const Vint*>(value)->content;
//        Kint* k2;
//        k2 = new Kint(c % MOD);
//
//        Vsum* v2 = new Vsum(c);
//
//        emit2(k2, v2, context);
//    }
//
//    // sums
//    virtual void reduce(const IntermediateVec* pairs, void* context) const {
//        const int key = static_cast<const Kint*>(pairs->at(0).first)->key;
//        ulong sum = 0;
//        for(const IntermediatePair& pair: *pairs) {
//            sum += static_cast<const Vsum*>(pair.second)->sum;
//            delete pair.first;
//            delete pair.second;
//        }
//        Kint* k3 = new Kint(key);
//        Vsum* v3 = new Vsum(sum);
//        emit3(k3, v3, context);
//    }
//};
//
//
//int main(int argc, char** argv)
//{
//    modsumClient client;
//    InputVec inputVec;
//    OutputVec outputVec;
//
//    Vint inputs[INPUTS];
//    for (int i = 0; i < INPUTS; i++){
//        inputs[i].content = rand() % (5*MOD);
//        inputVec.emplace_back(InputPair({nullptr, inputs + i}));
//    }
//
//    JobHandle job = startMapReduceJob(client, inputVec, outputVec, 50);
//
//
//    waitForJob(job);
//
////    for (OutputPair& pair: outputVec) {
//    for(unsigned long i = (outputVec.size() - 1) ; i > 0 ; --i ) {
//        auto pair = outputVec[i];
//        int key = ((const Kint*)pair.first)->key;
//        ulong sum = ((const Vsum*)pair.second)->sum;
//        printf("The sum of numbers whose mod%d == %d is %lu\n", MOD, key, sum);
//        delete pair.first;
//        delete pair.second;
//    }
//
//    closeJobHandle(job);
//
//    return 0;
//}





////Eurovision:
///**
// *
// * @author: Hadas Jacobi, 2018.
// *
// * This client reads the file points_awarded.h - Eurovision data from 1975-2016.
// * It then finds the winner from each year, and counts how many wins each country had.
// *
// */
//
//#include <cstdio>
//#include <iostream>
//#include <sstream>
//#include <array>
//#include <fstream>
//#include <vector>
//#include "MapReduceFramework.h"
//
//typedef std::pair<std::string, int> Points_received_by_country;
//typedef std::vector<Points_received_by_country> Points_in_year;
//
//// K1 is the year the Eurovision happened
//class Kyear : public K1 {
//public:
//    Kyear(int year) : year(year) {}
//
//    int year;
//
//    virtual bool operator<(const K1 &other) const {
//        return year < static_cast<const Kyear&>(other).year;
//    }
//};
//
//
//// V1 is a vector of {country, points_received} for all countries that participated that year
//class Vpointlist : public V1 {
//public:
//    Vpointlist(Points_in_year pointlist) : pointlist(pointlist) {}
//
//    Points_in_year pointlist;
//};
//
//
//// K2 & K3 are the winners of each year
//class Kwinner : public K2, public K3 {
//public:
//    Kwinner(std::string country) : country(country) {}
//
//    std::string country;
//
//    virtual bool operator<(const K2 &other) const {
//        return country < static_cast<const Kwinner&>(other).country;
//    }
//    virtual bool operator<(const K3 &other) const {
//        return country < static_cast<const Kwinner&>(other).country;
//    }
//};
//
//
//// V3 is the total number of wins
//class Vwins : public V3 {
//public:
//    Vwins(int wins) : wins(wins) {}
//
//    int wins;
//};
//
//
//
//class eurovisionClient : public MapReduceClient {
//public:
//    /**
//     * Finds the winning country for each year by choosing the country that received the most
//     * points.
//     */
//    void map(const K1 *key, const V1 *value, void *context) const {
//        Points_in_year pointlist = static_cast<const Vpointlist *>(value)->pointlist;
//        Points_received_by_country winner = pointlist[0];
//        for (auto country_points : pointlist){
//            if (country_points.second > winner.second){
//                winner = {country_points.first, country_points.second};
//            }
//        }
//
//        int year = static_cast<const Kyear *>(key)->year;
////        std::cout << "Winner for " << year << ": " << winner.first << "\n";
//
//        Kwinner* k2 = new Kwinner(winner.first);
//        emit2(k2, nullptr, context);
//    }
//
//    /**
//     * Counts how many wins in total a country had.
//     */
//    virtual void reduce(const IntermediateVec *pairs,
//                        void *context) const {
//        std::string country = static_cast<const Kwinner *>(pairs->at(0).first)->country;
//
//        int wins = pairs->size();
//        for (const IntermediatePair &pair: *pairs) {
//            delete pair.first;
//            delete pair.second;
//        }
//        Kwinner* k3 = new Kwinner(country);
//        Vwins* v3 = new Vwins(wins);
//        emit3(k3, v3, context);
//    }
//
//    virtual void printt(IntermediateVec & v) const {
//
//        for (IntermediatePair& pair: v) {
//            std::string country = ((const Kwinner*)pair.first)->country;
//            int wins = ((const Vwins*)pair.second)->wins;
//            printf("%s: %d win\n", country.c_str(), wins);
//
//        }
//
//    }
//
//
//};
//
//void process_data(std::string path, InputVec* inputVec){
//    std::ifstream input_file;
//    input_file.open(path);
//
//    std::string line;
//    if(input_file.is_open())
//    {
//        while(std::getline(input_file, line)) //get 1 row as a string
//        {
//            Points_in_year points_in_year(0);
//
//            std::istringstream iss(line); // put line into stringstream
//            int raw_year;
//            iss >> raw_year;
//
//            std::string country;
//            int points;
//            while(iss >> country >> points) //country by country
//            {
//                points_in_year.emplace_back(Points_received_by_country(country, points));
//            }
//
//            Kyear* year = new Kyear(raw_year);
//            Vpointlist* pointlist = new Vpointlist(points_in_year);
//
//            inputVec->emplace_back(std::pair<Kyear*, Vpointlist*>(year, pointlist));
//        }
//    }
//}
//
//
//int main(int argc, char **argv) {
//    eurovisionClient client;
//    InputVec inputVec;
//    OutputVec outputVec;
//
//    // TODO - enter your path to "new_clients/points_awarded.in"
//    process_data("/cs/usr/baraloni/Downloads/points_awarded.in", &inputVec);
//
//
//    JobHandle job = startMapReduceJob(client, inputVec, outputVec, 40);
//    waitForJob(job);
//
//    printf("Total Eurovision wins 1975-2016:\n");
//    for (OutputPair& pair: outputVec) {
//        std::string country = ((const Kwinner*)pair.first)->country;
//        int wins = ((const Vwins*)pair.second)->wins;
//        printf("%s: %d win%s\n",
//               country.c_str(), wins, wins > 1 ? "s" : "");
//        delete pair.first;
//        delete pair.second;
//    }
//
//
//    for (auto i : inputVec) {
//        delete i.first;
//        delete i.second;
//    }
//
//    closeJobHandle(job);
//
//    return 0;
//}









///reu:
//// ------------------------------ includes ------------------------------
//#include "MapReduceClient.h"
//#include "MapReduceFramework.h"
//#include <stdio.h>
//#include <signal.h>
//#include <sys/time.h>
//#include <setjmp.h>
//#include <unistd.h>
//#include "string.h"
//#include <unistd.h>
//#include <queue>
//#include <iostream>
//#include <dirent.h>
//#include <sys/stat.h>
//#include <iostream>
//#include <fstream>
//// -------------------------- using definitions -------------------------
//using namespace std;
//// -------------------------- definitions -------------------------------
//typedef std::vector<InputPair> IN_ITEMS_LIST;
//typedef std::pair<K1*, V1*> IN_ITEM;
//typedef std::vector<OutputPair> OUT_ITEMS_LIST;
//typedef std::pair<K3*, V3*> OUT_ITEM;
//
//class FileToSearch : public K1 {
//public:
//    char* file;
//    bool operator<(const K1 &other) const{
//        return true;
//    }
//};
//
//class WordToSearch : public V1 {
//public:
//    string word;
//};
//
//class Word : public K2 {
//public:
//    char* word;
//    bool operator<(const K2 &other) const{
//        Word* temp = (Word*) &other;
//        Word* temp2 = (Word*) this;
//        if(strcmp(temp -> word, temp2 -> word) <= 0){
//            return false;
//        }
//        return true;
//    }
//};
//
//class ApperanceOfWord : public V2 {
//public:
//    int num;
//};
//
//
//class Word2 : public K3 {
//public:
//    char* word2;
//    bool operator<(const K3 &other) const{
//        Word2* temp = (Word2*) &other;
//        Word2* temp2 = (Word2*) this;
//        if(strcmp(temp2 -> word2, temp -> word2) < 0){
//            return true;
//        }
//        return false;
//    }
//};
//
//class ApperanceOfWordList : public V3{
//public:
//    int num;
//};
//
//class Count : public MapReduceClient{
//public:
//
//    void map(const K1 *const key, const V1 *const val, void* context) const{
//
//        DIR *dir;
//        struct dirent *ent;
//        const char* file = ((FileToSearch*) key) -> file;
//        ifstream myfile;
//        myfile.open(file);
//        string wordToSearch = ((WordToSearch*) val) -> word;
//        while (myfile.good())
//        {
//            string word;
//            myfile >> word;
//
//            if ( word == wordToSearch)
//            {
//                ApperanceOfWord* apperanceOfWord = new ApperanceOfWord();
//                apperanceOfWord -> num = 1;
//                Word* k2 = new Word();
//                k2 -> word = strdup(wordToSearch.c_str());
//                emit2(k2,apperanceOfWord, context);
//            }
//        }
//        myfile.close();
//
//    }
//
//    void reduce(const IntermediateVec* pairs,
//                void* context) const{
//
//        string word = static_cast<const Word*>(pairs->at(0).first)->word;
//        int count = 0;
//        for (IntermediatePair pairr : *pairs)
//        {
//            V2* val = pairr.second;
//            count += ((ApperanceOfWord*)val) -> num;
//        }
//
//        Word2* myWord2 = new Word2();
//        myWord2 -> word2 = strdup(word.c_str());
//
//        ApperanceOfWordList* apperanceOfWordList = new ApperanceOfWordList();
//        apperanceOfWordList -> num = count;
//
//        emit3(myWord2,apperanceOfWordList, context);
//    }
//};
//
//
//IN_ITEMS_LIST getData(int argc,char *argv[])
//{
//    IN_ITEMS_LIST res;
//
//    for (int i = 5; i < 10; ++i)
//    {
//        for (int j = 1; j < 5; ++j)
//        {
//            FileToSearch* file1 = new FileToSearch();
//            file1 -> file = argv[i];
//            WordToSearch* word1 = new WordToSearch();
//            word1 -> word = argv[j];
//            res.push_back(IN_ITEM(file1,word1));
//        }
//    }
//    return res;
//}
//
//int main(int argc,char *argv[])
//{
//    Count count;
//    IN_ITEMS_LIST res = getData(argc,argv);
//    for(IN_ITEM item : res)
//    {
//        FileToSearch* a = (FileToSearch*) item.first;
//        WordToSearch* b = (WordToSearch*) item.second;
//    }
//
//    struct timeval diff, startTV, endTV;
//    OUT_ITEMS_LIST finalRes;
//
//    JobHandle job = startMapReduceJob(count, res ,finalRes, 1);
//    closeJobHandle(job);
//
//    cout << "***************************************" << endl;
//    cout << "uncle sam has a farm,but all his animals escaped and hid" << endl;
//    cout << "kids,help uncle sam find his animals in the files" << endl;
//    cout << "***************************************" << endl;
//    cout << "Recieved: " << endl;
//
//    for(OUT_ITEM& temp : finalRes)
//    {
//
//        Word2* temp1 = (Word2*) temp.first;
//        ApperanceOfWordList* temp2 = (ApperanceOfWordList*) temp.second;
//        cout << temp2 -> num << " "<< temp1 -> word2 << endl;
//    }
//
//    cout << "***************************************" << endl;
//    cout << "Excpected: " << endl;
//    cout << "(the order matter,mind you)" << endl;
//    cout << "6 Cat " << endl;
//    cout << "12 Dog " << endl;
//    cout << "10 Fish " << endl;
//    cout << "8 Sheep " << endl;
//
//    return 0;
//}







//grids:
//#include <fstream>
//#include <iostream>
//#include "Tests/GridMapReduce.hpp"
//#include "MapReduceClient.h"
//#include "MapReduceFramework.h"
//
//
//#define NUM_THREADS 8
//
//
//void runSingleGrid(std::ifstream& ifs, std::ofstream& ofs)
//{
//    InputVec k1v1Pairs;
//
//    // create the input vector
//    int row = 1;
//    std::string line;
//    while (std::getline(ifs, line))
//    {
//        Index* k = new Index(row);
//        RowString* v = new RowString(line);
//        k1v1Pairs.push_back(InputPair(k, v));
//
//        row++;
//    }
//
//
//    // create MapReduceBase object
//    GridMapReduce gmr;
//
//    // let the framework do the magic
//    OutputVec shamans;
//    JobHandle job = startMapReduceJob(gmr, k1v1Pairs, shamans, NUM_THREADS);
//
//    closeJobHandle(job);
//
//    // writing results to file
//    for (auto it = shamans.begin(); it != shamans.end(); ++it)
//    {
//        GridPoint& point = *(GridPoint*) (it->first);
//        int value = ((GridPointVal*) it->second)->getValue();
//        ofs << point.getRow() << " " << point.getCol()
//            << " " << value << std::endl;
//    }
//
//}
//
//
//int main(int argc, char* argv[])
//{
//    if (argc < 2)
//    {
//        std::cerr << "Usage: GridShamansFinder <path/to/grid>" << std::endl;
//        return 1;
//    }
//
//    std::string gridPath(argv[1]);
//
//    std::ifstream ifs(gridPath);
//    std::ofstream ofs(gridPath + std::string("_test_results"),
//                      std::ofstream::out);
//
//    if (!ifs.is_open() || !ofs.is_open())
//    {
//        std::cerr << "I/O Error occurred - couldn't open input or output file"
//                  << std::endl;
//        return 0;
//    }
//
//
//    runSingleGrid(ifs, ofs);
//    ifs.close();
//    ofs.close();
//}






//Scripts
//#include "WordFrequenciesClient.hpp"
//#include <algorithm>
//#include <zconf.h>
//
//#define NUM_THREADS 8
//
//void writeByFrequency(OutputVec& frequencies, std::ofstream& ofs)
//{
//
//    // get length of longest word (so we can write to the file in a nice format)
//    unsigned int maxLength = 0;
//    for (auto it = frequencies.begin(); it != frequencies.end(); ++it)
//    {
//        unsigned int length = (*(Word*) it->first).getWord().length();
//        maxLength = length > maxLength ? length : maxLength;
//    }
//
//    // sort by frequency is descending order
//    std::sort(
//            frequencies.begin(),
//            frequencies.end(),
//            [](const OutputPair& o1, const OutputPair& o2)
//            {
//                // o1 comes before o2 if the frequency of o1 is higher OR
//                // they have the same frequency and o1 comes before o2 in
//                // lexicographic order
//
//                if (((Integer*) o1.second)->val < ((Integer*) o2.second)->val)
//                    return false;
//
//                return ((Integer*) o1.second)->val > ((Integer*) o2.second)->val
//                       || ((Word*)o1.first)->getWord() < ((Word*)o2.first)->getWord();
//            }
//    );
//
//    // writing results to file
//    for (auto it = frequencies.begin(); it != frequencies.end(); ++it)
//    {
////        std::cout << (*(Word*) it->first).getWord() << std::endl;
//        const std::string& word = (*(Word*) it->first).getWord();
//        int frequency = ((Integer*) it->second)->val;
//        ofs << word;
//        for (int i = word.length(); i < maxLength + 5; ++i)
//        {
//            // pad with spaces
//            ofs << " ";
//        }
//        ofs << frequency << std::endl;
//    }
//
//}
//
//void findWordFrequencies(std::ifstream& ifs, std::ofstream& ofs)
//{
//    InputVec k1v1Pairs;
//
//    // make the input for the framework
//    std::string line;
//    while (std::getline(ifs, line))
//    {
//        Line* k1 = new Line(line);
//        k1v1Pairs.push_back(InputPair(k1, nullptr));
//    }
//
//    MapReduceWordFrequencies mapReduceObj;
//    OutputVec frequencies;
//
//    JobHandle job = startMapReduceJob(mapReduceObj, k1v1Pairs,frequencies, NUM_THREADS);
//
//
//    closeJobHandle(job);
//
//    writeByFrequency(frequencies, ofs);
//}
//
//
//int main(int argc, char* argv[])
//{
//    if (argc < 2)
//    {
//        std::cerr << "Usage: WordFrequencies <path/to/text_file>" << std::endl;
//        return 1;
//    }
//    std::cout << argv[1] << std::endl;
//    std::string textPath(argv[1]);
//    std::ifstream ifs(textPath);
//    std::ofstream ofs(textPath + std::string("_test_results"),
//                      std::ofstream::out);
//
//    if (!ifs.is_open() || !ofs.is_open())
//    {
//        std::cerr << "I/O Error occurred - couldn't open input or output file"
//                  << std::endl;
//        return 1;
//    }
//
//
//    findWordFrequencies(ifs, ofs);
//    ifs.close();
//    ofs.close();
//
//}








///--------------------Concurrency:




////Test_2:
#include "MapReduceFramework.h"
#include <cstdio>
#include <string>
#include <array>
#include <fstream>

class VString : public V1 {
public:
    VString(std::string content) : content(content) {}

    std::string content;
};

class KChar : public K2, public K3 {
public:
    KChar(char c) : c(c) {}

    virtual bool operator<(const K2 &other) const {
        return c < static_cast<const KChar &>(other).c;
    }

    virtual bool operator<(const K3 &other) const {
        return c < static_cast<const KChar &>(other).c;
    }

    char c;
};

class VCount : public V2, public V3 {
public:
    VCount(int count) : count(count) {}

    int count;
};


class CounterClient : public MapReduceClient {
public:
    void map(const K1 *key, const V1 *value, void *context) const {
        std::array<int, 256> counts;
        counts.fill(0);
        for (const char &c : static_cast<const VString *>(value)->content) {
            counts[(unsigned char) c]++;
        }

        for (int i = 0; i < 256; ++i) {
            if (counts[i] == 0)
                continue;

            KChar *k2 = new KChar(i);
            VCount *v2 = new VCount(counts[i]);
            emit2(k2, v2, context);
        }
    }

    virtual void reduce(const IntermediateVec *pairs,
                        void *context) const {
        const char c = static_cast<const KChar *>(pairs->at(0).first)->c;
        int count = 0;
        for (const IntermediatePair &pair: *pairs) {
            count += static_cast<const VCount *>(pair.second)->count;
            delete pair.first;
            delete pair.second;
        }
        KChar *k3 = new KChar(c);
        VCount *v3 = new VCount(count);
        emit3(k3, v3, context);
    }
};

typedef struct args {
    CounterClient *client1;
    InputVec *inputVec1;
    OutputVec *outputVec1;
    int num;
};


void *foo(void *arg) {
    auto *arg1 = (args *) arg;
    CounterClient *client = arg1->client1;
    InputVec *inputVec = arg1->inputVec1;
    OutputVec *outputVec = arg1->outputVec1;
    int num = arg1->num;
    auto job = startMapReduceJob(*client, *inputVec, *outputVec, num);
    waitForJob(job);
    return nullptr;
};

int main(int argc, char **argv) {
    int files_num = (int) *(argv[1]) - 48;
    pthread_t tids[files_num];
    args arguments[files_num];
    CounterClient *client;
    client = new CounterClient();

    for (int i = 0; i < files_num; ++i) {
        InputVec *inputVec;
        inputVec = new InputVec();
        OutputVec *outputVec;
        outputVec = new OutputVec();
        std::string line;
        std::string address = "/cs/usr/baraloni/Downloads/OSex3/Tests/text_gen/text_"+ std::to_string(i + 1);
        std::ifstream input_file1(address);

        while (std::getline(input_file1, line)) {

            VString *s = new VString(line);
            inputVec->push_back({nullptr, s});
        }
        arguments[i] = {client, inputVec, outputVec, 100};
        pthread_create(&(tids[i]), NULL, foo, (void *) &(arguments[i]));

    }


//    CounterClient *client2;
//    client2 = new CounterClient();
//    InputVec *inputVec2;
//    inputVec2 = new InputVec();
//    OutputVec *outputVec2;
//    outputVec2 = new OutputVec();
//
//    std::string line;
//    std::ifstream input_file1("/home/michaelbere/Documents/OS/ex3/text_gen/text_1");
//    std::ifstream input_file2("/home/michaelbere/Documents/OS/ex3/text_gen/text_2");
//    inputVec2->reserve(10000);
//
//    while (std::getline(input_file2, line)) {
//        VString *s = new VString(line);
//        inputVec2->push_back({nullptr, s});
//    }
//
//
//    args arg2 = {client2, inputVec2, outputVec2, 1};
//    pthread_create(&tid2, NULL, foo, (void *) &arg2);
//    runMapReduceFramework(client, inputVec, outputVec, 1);
//    for (int j = 0; j < files_num; ++j) {
//        pthread_join(tids[j], nullptr);
//    }
//    pthread_join(tid2, nullptr);
    for (int k = 0; k < files_num; ++k) {
        pthread_join(tids[k], nullptr);
        printf("File %d:\n", k + 1);
        for (OutputPair &pair: *(arguments[k].outputVec1)) {
            char c = ((const KChar *) pair.first)->c;
            int count = ((const VCount *) pair.second)->count;
            printf("The character %c appeared %d time%s\n",
                   c, count, count > 1 ? "s" : "");
            delete pair.first;
            delete pair.second;
        }
    }

//    printf("File 2:\n");
//    for (OutputPair &pair: *outputVec2) {
//        char c = ((const KChar *) pair.first)->c;
//        int count = ((const VCount *) pair.second)->count;
//        printf("The character %c appeared %d time%s\n",
//               c, count, count > 1 ? "s" : "");
//        delete pair.first;
//        delete pair.second;
//    }

    return 0;
}













//Tarantino:
///**
// * See README file.
// */
//#include "MapReduceClient.h"
//#include "MapReduceFramework.h"
//#include "WordFrequenciesClient.hpp"
//#include <algorithm>
//#include <zconf.h>
//
//using std::cout;
//using std::endl;
//using std::cerr;
//using std::sort;
//using std::string;
//using std::ifstream;
//using std::ofstream;
//using std::vector;
//
//// TODO: Play with this path to match your directories
//const string SCRIPTS_DIR = "/cs/usr/baraloni/Downloads/OSex3/Tests/scripts/";
//const int REPORT_FREQ_MS = 500;
//
//class ScriptJob
//{
//public:
//    JobHandle handle;
//    int id;
//    string path;
//    ifstream ifs;
//    ofstream ofs;
//    InputVec input;
//    OutputVec output;
//    JobState state;
//    bool initiated;
//
//    ScriptJob(const int id, const string &scriptPath) : id(id), path(scriptPath), input(),
//                                                        output(), state{UNDEFINED_STAGE, 0},
//                                                        initiated(false)
//    {
//        // Init files
//        string outPath(scriptPath + string("_test_results"));
//        ifs = ifstream(scriptPath);
//        ofs = ofstream(outPath, ofstream::out);
//        if (!ifs.is_open() || !ofs.is_open())
//        {
//            cerr << "I/O Error occurred - couldn't open input or output file" << endl;
//            return;
//        }
//
//        // Generate input vector
//        string line;
//        while (getline(ifs, line))
//        {
//            Line *k1 = new Line(line);
//            input.push_back(InputPair(k1, nullptr));
//        }
//
//        initiated = true;
//    }
//
//    ~ScriptJob()
//    {
//        ifs.close();
//        ofs.close();
//    }
//
//    void start(const MapReduceClient &client, const int &mtLevel)
//    {
//        if (!initiated)
//        {
//            return;
//        }
//        cout << "Starting job on file: " << path << endl;
//        handle = startMapReduceJob(client, input, output, mtLevel);
//    }
//
//    bool isDone()
//    {
//        return state.stage == REDUCE_STAGE && state.percentage == 100.0;
//    }
//
//    bool reportChange()
//    {
//        JobState newState;
//        getJobState(handle, &newState);
//        if (newState.stage != state.stage || newState.percentage != state.percentage)
//        {
//            printf("Thread [%d]: at stage [%d], [%f]%% \n", id, state.stage, state.percentage);
//            state = newState;
//            if (isDone())
//            {
//                printf("Thread [%d] done!\n", id);
//                return true;
//            }
//        }
//        return isDone();
//    }
//
//    void writeByFrequency()
//    {
//        // get length of longest word (so we can write to the file in a nice format)
//        unsigned int maxLength = 0;
//        for (auto &frequencie : output)
//        {
//            auto length = static_cast<unsigned int>((*(Word *) frequencie.first).getWord().length());
//            maxLength = length > maxLength ? length : maxLength;
//        }
//
//        // Sort by frequency in descending order
//        sort(output.begin(), output.end(),
//             [](const OutputPair &o1, const OutputPair &o2) {
//                 // o1 comes before o2 if the frequency of o1 is higher OR
//                 // they have the same frequency and o1 comes before o2 in
//                 // lexicographic order
//
//                 if (((Integer *) o1.second)->val < ((Integer *) o2.second)->val)
//                 {
//                     return false;
//                 }
//
//                 return ((Integer *) o1.second)->val > ((Integer *) o2.second)->val
//                        || ((Word *) o1.first)->getWord() < ((Word *) o2.first)->getWord();
//             }
//        );
//
//        // Writ results to file
//        for (auto &pair : output)
//        {
//            // cout << (*(Word*) it->first).getWord() << endl;
//            const string &word = (*(Word *) pair.first).getWord();
//            int frequency = ((Integer *) pair.second)->val;
//            ofs << word;
//            for (unsigned long i = word.length(); i < maxLength + 5; ++i)
//            {
//                // pad with spaces
//                ofs << " ";
//            }
//            ofs << frequency << endl;
//            delete pair.first;
//            delete pair.second;
//        }
//    }
//};
//
//int main()
//{
//    vector<ScriptJob *> jobs;
//    vector<string> paths;
//
//    paths.emplace_back(SCRIPTS_DIR + "Inglourious_Basterds");
//    paths.emplace_back(SCRIPTS_DIR + "Reservoir_Dogs");
//    paths.emplace_back(SCRIPTS_DIR + "Pulp_Fiction");
//
//    // Generate jobs
//    jobs.reserve(paths.size());
//
//    int idCount = 1;
//    for (const auto &path : paths)
//    {
//        jobs.push_back(new ScriptJob(idCount++, path));
//    }
//
//    // Start jobs
//    MapReduceWordFrequencies client;
//    int mtLevel = 1;
//    for (auto job :jobs)
//    {
//        job->start(client, mtLevel);
//        mtLevel *= 2;
//    }
//
//    // Job 0 will take the longest, report
//    while (!jobs[0]->isDone())
//    {
//        for (auto job : jobs)
//        {
//            job->reportChange();
//        }
//        usleep(REPORT_FREQ_MS * 10);
//    }
//
//    // Make sure everyone is dead
//    for (auto job :jobs)
//    {
//        waitForJob(job->handle);
//    }
//
//    // Write output
//    for (auto job :jobs)
//    {
//        job->writeByFrequency();
//    }
//
//    // Kill
//    for (auto job :jobs)
//    {
//        closeJobHandle(job->handle);
//    }
//
//    // Delete pointers
//    while (!jobs.empty())
//    {
//        ScriptJob *job = jobs.back();
//        delete job;
//        jobs.pop_back();
//    }
//
//    cout << endl;
//    cout << "If you got here with no memory leaks, it's a good sign." << endl;
//    cout << "Don't forget to verify the 'test_results' files with diff." << endl;
//
//}


///----------------------------Not compatible:


////Bnaya:
//#include <iostream>
//#include "MapReduceClient.h"
//#include "MapReduceFramework.h"
//
//#define RUN_TEST(functionMame) if(functionMame()){ \
//    std::cout << #functionMame << " OK" << std::endl;\
//   }\
//       else{\
//        std::cout << #functionMame << " FAILED" << std::endl;\
//       }
//
//
//class AKey : public k1Base, public k2Base, public k3Base
//{
//public:
//    AKey(int i): m_i(i)
//    {
//    }
//
//    int getInt() const
//    {
//        return m_i;
//    }
//
//
//    virtual bool operator<(const k2Base &other) const
//    {
//        return m_i < dynamic_cast<const AKey&>(other).m_i;
//    }
//    virtual bool operator<(const k3Base &other) const
//    {
//        return m_i < dynamic_cast<const AKey&>(other).m_i;
//    }
//    virtual bool operator<(const k1Base &other) const
//    {
//        return m_i < dynamic_cast<const AKey&>(other).m_i;
//    }
//private:
//    int m_i;
//};
//
//class SameKey :  public k1Base, public k2Base, public k3Base
//{
//public:
//    SameKey(int i): m_i(i)
//    {
//    }
//
//    virtual bool operator<(const k2Base &other) const
//    {
//        (void)other;
//        return false;
//    }
//
//    virtual bool operator<(const k3Base &other) const
//    {
//        (void)other;
//        return false;
//    }
//
//    virtual bool operator<(const k1Base &other) const
//    {
//        (void)other;
//        return false;
//    }
//private:
//    int m_i;
//};
//
//class IntVal: public v3Base
//{
//public:
//    IntVal(int i):m_i(i)
//    {
//    }
//    int getInt() const
//    {
//        return m_i;
//    }
//private:
//    int m_i;
//};
//
//class MyMapReduce: public MapReduceBase
//{
//    void Map(const k1Base *const key, const v1Base *const val) const
//    {
//        Emit2(dynamic_cast<k2Base*>(const_cast<k1Base*>(key)), nullptr);
//        (void)val;
//    }
//
//    void Reduce(const k2Base *const key, const V2_LIST &vals) const
//    {
//        IntVal* val = new IntVal(vals.size());
//        Emit3(dynamic_cast<k3Base*>(const_cast<k2Base*>(key)), val);
//    }
//};
//
//bool eachInputHandleOnce()
//{
//    bool testResult = true;
//    MyMapReduce mapReduce;
//    IN_ITEMS_LIST list;
//    for (int i = 0; i< 100000;i++)
//    {
//        list.push_back(IN_ITEM(new AKey(i),nullptr));
//    }
//    OUT_ITEMS_LIST result = runMapReduceFramework(mapReduce, list, 100);
//
//
//    for( OUT_ITEM& item: result)
//    {
//        if (1 != dynamic_cast<IntVal*>(item.second)->getInt())
//        {
//            testResult = false;
//        }
//    }
//
//    for (IN_ITEM& item: list)
//    {
//        delete item.first;
//    }
//
//    for( OUT_ITEM& item: result)
//    {
//        delete item.second;
//    }
//
//    return testResult;
//}
//
//bool outputIsOrdered()
//{
//    bool testResult = true;
//    MyMapReduce mapReduce;
//    IN_ITEMS_LIST list;
//    for (int i = 100000; i>= 0;i--)
//    {
//        list.push_back(IN_ITEM(new AKey(i),nullptr));
//    }
//    OUT_ITEMS_LIST result = runMapReduceFramework(mapReduce, list, 100);
//
//    int i = 0;
//    for( OUT_ITEM& item: result)
//    {
//        if (i != dynamic_cast<const AKey*>(item.first)->getInt())
//        {
//            testResult = false;
//        }
//        i++;
//    }
//
//    for (IN_ITEM& item: list)
//    {
//        delete item.first;
//    }
//
//    for( OUT_ITEM& item: result)
//    {
//        delete item.second;
//    }
//
//    return testResult;
//}
//
//
//bool useOperatorForCompare()
//{
//    bool testResult = true;
//    MyMapReduce mapReduce;
//    IN_ITEMS_LIST list;
//    for (int i = 0; i< 100000;i++)
//    {
//        list.push_back(IN_ITEM(new SameKey(i),nullptr));
//    }
//    OUT_ITEMS_LIST result = runMapReduceFramework(mapReduce, list, 100);
//
//    if (1 != result.size())
//    {
//        testResult = false;
//    }
//
//    for( OUT_ITEM& item: result)
//    {
//        if (100000 != dynamic_cast<IntVal*>(item.second)->getInt())
//        {
//            testResult = false;
//        }
//    }
//
//    for (IN_ITEM& item: list)
//    {
//        delete item.first;
//    }
//
//    for( OUT_ITEM& item: result)
//    {
//        delete item.second;
//    }
//    return testResult;
//}
//
//
//int main()
//{
//    RUN_TEST(eachInputHandleOnce);
//    RUN_TEST(outputIsOrdered);
//    RUN_TEST(useOperatorForCompare);
//}


////Era:
//#include <iostream>
//#include "MapReduceClient.h"
//#include "MapReduceFramework.h"
//
//
//using namespace std;
//
//// All the user implemented classes
//class k1Derived: public K1
//{
//public:
//    int myNum;
//    k1Derived(int x): myNum(x){};
//    ~k1Derived(){};
//    bool operator<(const K1 &other) const
//    {
//        return ((const k1Derived&) other).myNum < myNum;
//    }
//};
//
//class v1Derived: public V1
//{
//    ~v1Derived();
//};
//class k2Derived: public K2
//{
//public:
//    int myNum;
//    k2Derived(int x): myNum(x){};
//    ~k2Derived(){}
//    bool operator<(const K2 &other) const
//    {
//        return  myNum < ((const k2Derived&) other).myNum;
//    }
//};
//
//class v2Derived: public V2
//{
//public:
//    int myNum;
//    v2Derived(int x): myNum(x){};
//    ~v2Derived(){}
//};
//
//class k3Derived: public K3
//{
//public:
//    int myNum;
//    k3Derived(int x): myNum(x){};
//    ~k3Derived(){}
//    bool operator<(const K3 &other) const
//    {
//        return myNum<((const k3Derived&) other).myNum;
//    }
//
//};
//
//class v3Derived: public V3
//{
//public:
//    int myNum;
//    v3Derived(int x): myNum(x){};
//    ~v3Derived(){}
//
//};
//
//class derivedMapReduce: public MapReduceClient {
//
//    void map(const K1 * key, const V1 * value, void* context) const override {
//        k2Derived* convertedK2 = new k2Derived(((const k1Derived *const) key)->myNum);
//        v2Derived* newV2 = new v2Derived(1);
//        emit2((K2 *) convertedK2, (V2 *) newV2, context);
//    }
//
//
//    void reduce(const IntermediateVec* pairs, void* context) const override {
//        int key = static_cast<const k2Derived *>(pairs->at(0).first)->myNum;
//
//        int val = pairs->size();
//        for (const IntermediatePair &pair: *pairs) {
//            delete pair.first;
//            delete pair.second;
//        }
//
//        k3Derived* convertedK3 = new k3Derived(key);
//        v3Derived* newV3 = new v3Derived(val);
//        emit3((K3 *) convertedK3, (V3 *) newV3, context);
//    }
//};
//
//
//int NUM_THREADS = 20;
//int INNER_LOOP = 700;
//
//int NUM_START_OBJECTS = (INNER_LOOP*(INNER_LOOP-1))/2;
//int NUM_FINAL_CONTAINERS = INNER_LOOP-1;
//
//int main() {
//    derivedMapReduce dmp = derivedMapReduce();
//    InputVec iil = InputVec();
//    for (int i = 0; i < INNER_LOOP-1; ++i)
//    {
//        for (int j=i+1; j < INNER_LOOP; ++j)
//        {
//            k1Derived* currKey =  new k1Derived(j);
//            InputPair pair =  InputPair(currKey, nullptr);
//            iil.push_back(pair);
//        }
//    }
//    OutputVec oil;
//
//    JobHandle job = startMapReduceJob( dmp,  iil, oil, NUM_THREADS);
//
//    closeJobHandle(job);
//
//    for(auto it= iil.begin(); it != iil.end(); it++)
//    {
//        delete (*it).first;
//        delete (*it).second;
//    }
//    for(auto it = oil.begin(); it != oil.end(); it++)
//    {
//        std::cout << ((k3Derived*)(it->first))->myNum << ": " << ((v3Derived*)(it->second))->myNum << std::endl;
//        delete it->first;
//        delete it->second;
//
//    }
//    std::cout << "AMOUNT OF BUCKETS" << oil.size() << std::endl;
//    return 0;
//}
