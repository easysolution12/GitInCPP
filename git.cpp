#include <bits/stdc++.h>
using namespace std;

class Commit
{
private:
    string message;

public:
    //constructor
    Commit(string);
    string getMessage();
};

class Branch
{
private:
    //vector holds commits of respectively branches
    vector<Commit> commits;
    string branchName;

public:
    //constructor
    Branch(string);
    void addCommit();
    string getName();
    void printCommits();
};

//A Git repo represents a project
class Project
{
protected:
    //vector holds different branches in the project
    vector<Branch> branches;

    string curr_branch;

public:
    //to print the log of commits
    void log();
    //adds new branches
    void checkout(string branch_name);
    void makeMasterBranch();
    void getBranch();
};

//Directory class holds files(represented by strings)
class Directory
{
protected:
    //files in directory
    vector<string> files; // A name identifies a unique file
public:
    void addFile(string name);
    void listFiles();
};

//Represents staging area used to track non-commited files
class StagingArea : public Directory
{
protected:
    //files in staging area
    vector<bool> track; //boolean vector signifies which file is being tracked
public:
    //constructor
    StagingArea();
    void viewTrackedFiles();
    void viewUntrackedFiles();
    void addFilesToStagingArea(string);
};

class Repository : public StagingArea, public Project
{
private:
    //files already committed
    vector<bool> committed; //boolean vector signifies which file is being committed
public:
    //constructor
    Repository();
    void viewFilesInRepos();
    void addFilesToCommit();
};
