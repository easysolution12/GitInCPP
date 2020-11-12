#include "git_methods.cpp"
int main()
{
    int flag = 0;
    cout << "\nCommands menu: "
         << "\n1. git init"
         << "\n2. git add"
         << "\n3. git status"
         << "\n4. git commit -m "
         << "\n5.git branch"
         << "\n6.git checkout -b <branch_name>"
         << "\n7. git log"
         << "\n8. git checkout <branch_name>"
         << "\n9. git merge" << endl;

    char p = 'y';
    string command;
    Project project;
    StagingArea stagingArea;
    Directory directory;
    Repository repository;
    while (p == 'y')
    {

        cout << "\nEnter a command: ";
        cin >> command;
        if (command == "git init")
        {
            flag = 1;
            cout << "\nEmpty project has been initialised";
        }
        if (flag)
        {
            if (command.substr(0, 6) == "git add")
            {

                if (directory.isEmpty())
                {
                    cout << "\nAdd some files to your Directory!";
                    cout << "\nEnter how many files to add: ";
                    int t;
                    cin >> t;
                    for (int i = 0; i < t; i++)
                    {
                        string fileName;
                        cout << "\nEnter file name: ";
                        cin >> fileName;
                        directory.addFile(fileName);
                    }
                }
                else
                {
                    int temp = 1;
                    while (temp == 1)
                    {
                        cout << "\nEnter file to be added to the staging area: ";
                        string fileName;
                        cin >> fileName;
                        stagingArea.addFilesToStagingArea(fileName);
                        cout << "\nEnter 1 to add more files to staging area?";
                        cin >> temp;
                    }
                }
            }
            else if (command == "git status")
            {
                stagingArea.viewTrackedFiles();
                stagingArea.viewUntrackedFiles();
            }
            else if (command == "git branch")
            {
                project.getBranch();
            }
            else if (command == "git log")
            {
                project.log();
            }
            else if (command.substr(0, 11) == "git checkout")
            {
                string branchName = command.substr(13,command.size()-1);
                project.checkout(branchName);
            }
            else if (command.substr(0, 14) == "git checkout -b")
            {
                string branchName = command.substr(16,command.size()-1);
                project.checkout_b(branchName);
            }
            else if (command.substr(0, 8) == "git merge")
            {
                project.merge(command.substr(10,command.size()-1));
            }
            else if (command.substr(0, 12) == "git commit -m")
            {
                repository.copyStagingToRepo().addFilesToCommit();
            }
            else
            {
                cout << "\nInvalid command";
            }
        }
        cout << "\nDo you want to continue(y/n)? ";
        cin >> p;
    }

    return 0;
}

//ToDo:
//1. Check whether repo is initialised
//2. git add .
