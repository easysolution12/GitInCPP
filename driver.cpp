#include "git_methods.cpp"
int main()
{
    string command;
    bool c = true;
    while (c)
    {
        cout << endl
             << "Enter a command: ";
        cin >> command;
        if (command == "git init")
        {
            Project project_1;
            StagingArea stagingArea;
        }
        else if (command == "git add")
        {
        }
    }
    return 0;
}

//ToDo:
//1. Check whether repo is initialised