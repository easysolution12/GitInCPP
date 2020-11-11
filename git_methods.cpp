#include "git.cpp"

Commit::Commit(string message)
{
    this->message = message;
}

string Commit::getMessage()
{
    return message;
}

Branch::Branch(string branchName)
{
    this->branchName = branchName;
}

void Branch::addCommit()
{
    cout<<"\nEnter commit message: ";
    string message;
    cin >> message;
    Commit commit(message);
    commits.emplace_back(commit);
}

string Branch::getName()
{
    return branchName;
}

void Branch::printCommits()
{
    for (int i = 0; i < commits.size(); i++)
    {
        cout << commits[i].getMessage();
    }
}

void Project::log()
{
    for (int i = 0; i < branches.size(); i++)
    {
        cout << "Commits in branch " << branches[i].getName() << "/n";
        branches[i].printCommits();
        cout << endl;
    }
}

void Project::makeMasterBranch()
{
    if (branches.size() == 0)
    {
        Branch b1("Master");
        branches.emplace_back(b1);
        curr_branch = "Master";
    }
}

void Project ::getBranch(){
cout<<"Your current working branch is "<<curr_branch<<endl;
}

void Project ::checkout(string branch_name)
{
    for (int i = 0; i < branches.size(); i++)
    {
        if (branches[i].getName() == branch_name)
        {
            curr_branch = branch_name;
        }
        else
        {
            Branch b1(branch_name);
            branches.emplace_back(b1);
        }
    }
}

void Directory::addFile(string fileName)
{
    files.emplace_back(fileName);
}

void Directory::listFiles()
{
    cout << "\nFiles in the repository:\n";
    for (int i = 0; i < files.size(); i++)
    {
        cout << "\t"
             << files[i];
    }
}
//constructor
StagingArea::StagingArea()
{
    for (int i = 0; i < files.size(); i++)
    {
        track.emplace_back(false);
    }
    for (auto i = track.begin(); i != track.end(); i++)
    {
        cout << *i << " ";
    }
}
void StagingArea::viewTrackedFiles()
{
    cout << "\nFollowing files added to staging area:";
    for (int i = 0; i < track.size(); i++)
    {
        if (track[i])
        {
            cout << "\n"
                 << files[i];
        }
    }
}
void StagingArea::viewUntrackedFiles()
{
    cout << "\nFollowing files not added to staging area:";
    for (int i = 0; i < track.size(); i++)
    {
        if (!track[i])
        {
            cout << "\n"
                 << files[i];
        }
    }
}
void StagingArea ::addFilesToStagingArea(string file_name)
{
    auto it = find(files.begin(), files.end(), file_name);
    if (it != files.end())
    {
        int index = it - files.begin();
        track[index] = true;
    }
}

Repository::Repository()
{
    for (int i = 0; i < files.size(); i++)
    {
        track.emplace_back(false);
    }
    for (auto i = track.begin(); i != track.end(); i++)
    {
        cout << *i << " ";
    }
}

void Repository::viewFilesInRepos()
{
    cout << "\nFollowing files are present in the repository:";
    for (int i = 0; i < committed.size(); i++)
    {
        if (committed[i])
        {
            cout << "\n"
                 << files[i];
        }
    }
}

void Repository ::addFilesToCommit()
{
    makeMasterBranch();
    for (int i = 0; i < track.size(); i++)
    {
        committed[i] = track[i];
    }
    for (int i = 0; i < files.size(); i++)
    {
        if (committed[i])
        {
            cout << "\n"
                 << files[i];
        }
    }
    auto i = find(branches.begin(), branches.end(), curr_branch);
    if (i != branches.end())
    {
        int index = i - branches.begin();
        branches[index].addCommit();
    }
}
