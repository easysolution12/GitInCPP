#include "git.cpp"
using namespace std;
Commit::Commit(string message)
{
    this->message = message;
}

void Commit::showFiles()
{
    cout << "\nFiles in this commit are: ";
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
        filesInCommit.push_back(filesCommited[i]);
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
    getline(cin, message);
    Commit commit(message);
    commit.pushFilesCommitted(filesCommited);
    commits.push_back(commit);
}

string Branch::getName()
{
    return branchName;
}

void Branch::printCommits()
{
    for (int i = 0; i < commits.size(); i++)
    {
        cout << commits[i].getMessage() << " ";
    }
}

void Project::log()
{
    for (int i = 0; i < branches.size(); i++)
    {
        cout << "Commits in branch " << branches[i].getName() << "\n";
        branches[i].printCommits();
        cout << endl;
    }
}

//git merge branch_name
// void Project ::merge(string branch_name)
// {
//     vector<Branch> &branches = getBranches();
//     int i;
//     for (i = 0; i < branches.size(); i++)
//     {
//         if (branches[i].getName() == branch_name)
//         {
//             vector<Commit> &mergeCommits = branches[i].getCommits();
//             vector<Commit> &currBranchCommits = getBranch().getCommits();
//             int j;
//             // for (j = 0; j <= mergeCommits.size() -1 && j <= currBranchCommits.size()-1; j++)
//             // {
//             //     currBranchCommits[j] = mergeCommits[j];
//             // }
//             for (int k = 0; k < mergeCommits.size(); k++)
//             {
//                 currBranchCommits.push_back(mergeCommits[k]);
//             }
//             break;
//         }
//     }
//     if (i == branches.size())
//     {
//         cout << branch_name << " does not exist" << endl;
//     }
// }

void Project::makeMasterBranch()
{
    if (branches.size() == 0)
    {
        Branch b1("master");
        branches.push_back(b1);
        curr_branch = "master";
    }
}

Branch Project ::getBranch()
{
    int i;
    for (i = 0; i < branches.size(); i++)
    {
        if (branches[i].getName() == curr_branch)
        {
            return branches[i];
        }
    }
    return branches[i - 1];
}
string Project::getCurrBranch()
{
    return curr_branch;
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
    branches.push_back(b1);
    cout << "\nCreated a new branch " << branch_name << " and shifted.";
    curr_branch = branch_name;
}

vector<Branch> &Project ::getBranches()
{
    return branches;
}

void Directory::addFile(string fileName)
{
    files.push_back(fileName);
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
    if (files.size() == 0)
        return true;
    return false;
}
vector<string> &Directory ::getFiles()
{
    return files;
}

void StagingArea::copyToTrack(Directory &d)
{
    vector<string> s = d.getFiles();
    int i;
    for (int i = 0; i < s.size(); i++)
    {
        track.push_back(false);
    }
}

vector<bool> &StagingArea ::getTrack()
{
    return track;
}

void StagingArea::viewTrackedFiles(Directory &d)
{
    vector<string> s = d.getFiles();
    int i;
    cout << "\nFollowing files added to staging area:";
    for (i = 0; i < track.size(); i++)
    {
        if (track[i])
        {
            cout << "\n"
                 << s[i];
        }
    }
}
void StagingArea::viewUntrackedFiles(Directory &d)
{
    vector<string> s = d.getFiles();
    int i;
    cout << "\nFollowing files not added to staging area:";
    for (i = 0; i < track.size(); i++)
    {
        if (!track[i])
        {
            cout << "\n"
                 << s[i];
        }
    }
}

void StagingArea ::addFilesToStagingArea(string file_name, Directory &d)
{
    //cout<<d.files.size();
    vector<string> s = d.getFiles();
    int i;
    if (track.size() == 0)
    {
        copyToTrack(d);
    }
    for (i = 0; i < s.size(); i++)
    {

        if (s[i] == file_name)
        {

            track[i] = true;
            cout << "\nFile successfully added to the staging area";
            return;
        }
    }

    if (i == s.size())
    {
        cout << "\nGiven file does not exists";
    }
}

Repository &Repository::copyStagingToRepo(Directory &d)
{
    vector<string> files = d.getFiles();
    if (committed.size() == 0)
    {
        for (int i = 0; i < files.size(); i++)
        {
            committed.push_back(false);
        }
    }
    return *this;
}
void Repository::viewFilesInRepos(Directory &d)

{
    vector<string> files = d.getFiles();
    int i;
    cout << "\nFollowing files are present in the repository:";
    for (i = 0; i < committed.size(); i++)
    {
        if (committed[i])
        {
            cout << "\n"
                 << files[i];
        }
    }
}

void Repository ::addFilesToCommit(Directory &d, Project &p, StagingArea &t)
{
    vector<string> files = d.getFiles();
    int i;
    vector<bool> &track = t.getTrack();
    p.makeMasterBranch();
    vector<Branch> &branches = p.getBranches();

    for (i = 0; i < track.size(); i++)
    {
        committed[i] = track[i];
    }
    vector<string> filesCommited;
    for (i = 0; i < files.size(); i++)
    {

        if (committed[i])
        {
            filesCommited.push_back(files[i]);
        }
    }

    for (i = 0; i < branches.size(); i++)
    {

        if (branches[i].getName() == p.getCurrBranch())
        {

            branches[i].addCommit(filesCommited);
            break;
        }
    }
    if (i == branches.size())
    {
        cout << "\nThe given branch does not exists";
    }
}