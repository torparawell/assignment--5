#include "assignment-5.h"
using namespace std;

int main(int argc, char** argv){
    ManageDataBase *manageDataBase = new ManageDataBase();
    FileIO *fileIO = new FileIO(manageDataBase);
    manageDataBase->PromptUser();

    delete manageDataBase;
}
