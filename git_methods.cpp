#include "git.cpp"
using namespace std;
Commit::Commit(string message)
{
    this->message = message;
}

void Commit::showFiles()
{
    cout << "\nFiles in this branch are: ";
    for (int i = 0; i < filesInCommit.size(); i++)
    {
        cout << "\n"
             << filesInCommit[i];
    }
}

void Branch::showFiles(string message)
{
    for (int i = 0; i < commits.size(); i++)
    {
        if (commits[i].getMessage() == message)
        {
            commits[i].showFiles();
            return;
        }
    }
}

string Commit::getMessage()
{
    return message;
}

void Commit::pushFilesCommitted(vector<string> &filesCommited)
{
    for (int i = 0; i < filesCommited.size(); i++)
    {
        filesInCommit.emplace_back(filesInCommit[i]);
    }
}
vector<Commit> &Branch::getCommits()
{
    return commits;
}
Branch::Branch(string branchName)
{
    this->branchName = branchName;
}

void Branch::addCommit(vector<string> &filesCommited)
{
    cout << "\nEnter commit message: ";
    string message;
    cin >> message;
    Commit commit(message);
    commit.pushFilesCommitted(filesCommited);
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
//git merge branch_name
void Project ::merge(string branch_name)
{
    for (int i = 0; i < branches.size(); i++)
    {
        if (branches[i].getName() == branch_name)
        {
            vector<Commit> &mergeCommits = branches[i].getCommits();
            vector<Commit> &currBranchCommits = getBranch().getCommits();
            int j;
            for (j = 0; j < mergeCommits.size() && j < currBranchCommits.size(); j++)
            {
                currBranchCommits[j] = mergeCommits[j];
            }
            for (int k = j; k < mergeCommits.size(); k++)
            {
                currBranchCommits.emplace_back(mergeCommits[k]);
            }
        }
        else
        {
            cout << branch_name << " does not exist" << endl;
        }
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

Branch Project ::getBranch()
{
    cout << "Your current working branch is " << curr_branch << endl;
    for (int i = 0; i < branches.size(); i++)
    {
        if (branches[i].getName() == curr_branch)
        {
            return branches[i];
        }
    }
    return;
}

void Project ::checkout(string branch_name)
{
    int i;
    for (i = 0; i < branches.size(); i++)
    {
        if (branches[i].getName() == branch_name)
        {
            curr_branch = branch_name;
            cout << "\nShifted to " << curr_branch;
            break;
        }
    }
    if (i == branches.size())
    {
        cout << "\n"
             << branch_name << " does not exist";
    }
}

void Project::checkout_b(string branch_name)
{
    int i;
    for (i = 0; i < branches.size(); i++)
    {
        if (branches[i].getName() == branch_name)
        {

            return;
        }
    }
    Branch b1(branch_name);
    branches.emplace_back(b1);
    cout << "\nCreated a new branch " << branch_name << " and shifted.";
    curr_branch = branch_name;
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

bool Directory ::isEmpty()
{
    if (files.size())
        return true;
    return false;
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
        cout << "\nFile successfully added to the staging area";
    }
    else
    {
        cout << "\nGiven file does not exists!";
    }
}

Repository& Repository::copyStagingToRepo()
{
    for (int i = 0; i < files.size(); i++)
    {
        track.emplace_back(false);
    }
    for (auto i = track.begin(); i != track.end(); i++)
    {
        cout << *i << " ";
    }
    return *this;
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
    vector<string> filesCommited;
    for (int i = 0; i < files.size(); i++)
    {

        if (committed[i])
        {
            cout << "\n"
                 << files[i];
        }
        filesCommited.emplace_back(files[i]);
    }
    auto i = find(branches.begin(), branches.end(), curr_branch);
    if (i != branches.end())
    {
        int index = i - branches.begin();
        branches[index].addCommit(filesCommited);
    }
}
