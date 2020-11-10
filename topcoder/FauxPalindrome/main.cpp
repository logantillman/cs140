#include "FauxPalindromes.cpp"

int main(int argc, char **argv)
{
    int i;
    class FauxPalindromes TheClass;
    string retval;
    string word;
    string arg;

    if (argc != 2) { fprintf(stderr, "usage: a.out num\n"); exit(1); }
    arg = argv[1];

    if (arg == "-") {
        cin >> word;
    }
    else {

        if (atoi(argv[1]) == 0) {
            word = "ANA";
        }

        if (atoi(argv[1]) == 1) {
            word = "AAAAANNAA";
        }

        if (atoi(argv[1]) == 2) {
            word = "LEGENDARY";
        }

        if (atoi(argv[1]) == 3) {
            word = "XXXYTYYTTYX";
        }

        if (atoi(argv[1]) == 4) {
            word = "TOPCOODEREDOOCPOT";
        }

        if (atoi(argv[1]) == 5) {
            word = "TOPCODEREDOOCPOT";
        }

        if (atoi(argv[1]) == 6) {
            word = "XXXXYYYYYZZXXYYY";
        }
    }

    retval = TheClass.classifyIt(word);
    cout << retval << endl;

    exit(0);
}
