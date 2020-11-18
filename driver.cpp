#include "git_methods.cpp"
int main()
{
    cout << "\nCommands menu: "
         << "\n1. git init"
         << "\n2. git add"
         << "\n3. git status"
         << "\n4. git commit -m "
         << "\n5. git branch"
         << "\n6. git checkout -b <branch_name>"
         << "\n7. git log"
         << "\n8. git checkout <branch_name>"
         << "\n9. addFilesToDirectory"
         << "\n10. viewFilesInRepo"
         << "\n11. git merge"
         << "\n12. exit" << endl;

    char p = 'y';
    string command;
    Project project;
    StagingArea stagingArea;
    Directory directory;
    Repository repository;
    int flag = 0;
    while (p == 'y')
    {

        cout << "\nEnter a command: ";
        getline(cin, command);
        if (command == "git init")
        {
            flag = Project::updateAndReturnFlag();
            cout << "\nEmpty project has been initialised";
            continue;
        }
        if (flag)
        {
            if (command == "git add")
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
                        stagingArea.addFilesToStagingArea(fileName, directory);
                        cout << "\nEnter 1 to add more files to staging area?";
                        cin >> temp;
                    }
                }
            }
            else if (command == "addFilesToDirectory")
            {
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
            else if (command == "git status")
            {
                stagingArea.viewTrackedFiles(directory);
                stagingArea.viewUntrackedFiles(directory);
            }
            else if (command == "viewFilesInRepo")
            {
                repository.viewFilesInRepos(directory);
            }
            else if (command == "git branch")
            {
                cout << "\n"
                     << project.getCurrBranch();
            }

            else if (command == "git log")
            {
                project.log();
            }
            else if (command.substr(0, 15) == "git checkout -b")
            {

                string branchName = command.substr(16, command.size() - 1);
                project.checkout_b(branchName);
            }
            else if (command.substr(0, 12) == "git checkout")
            {
                string branchName = command.substr(13, command.size() - 1);
                project.checkout(branchName);
            }

            // else if (command.substr(0, 9) == "git merge")
            // {
            //     project.merge(command.substr(10, command.size() - 1));
            // }
            else if (command == "git commit -m")
            {
                repository.copyStagingToRepo(directory).addFilesToCommit(directory, project, stagingArea);
            }
            else
            {
                cout << "\nInvalid command";
            }
        }
        if (command == "exit")
        {
            break;
        }
        getchar();
    }

    return 0;
}
