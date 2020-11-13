#include <bits/stdc++.h>
using namespace std;

class Commit
{
private:
    string message;
    vector<string> filesInCommit; //holds files related to a commit
public:
    //constructor
    Commit(string);
    string getMessage();
    void pushFilesCommitted(vector<string> &);
    void showFiles();
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
    void addCommit(vector<string> &);
    string getName();
    void printCommits();
    void showFiles(string);
    vector<Commit> &getCommits();
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
    //shift to new branch
    void checkout(string branch_name);
    //creates a new branch
    void checkout_b(string branch_name);
    //makes master branch(if not)
    void makeMasterBranch();
    Branch getBranch();
    void merge(string branch_name);
    vector<Branch> & getBranches();
    string getCurrBranch();
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
    bool isEmpty();
    vector<string> &getFiles();
};

//Represents staging area used to track non-commited files
class StagingArea : public Directory
{
protected:
    //files in staging area
    vector<bool> track; //boolean vector signifies which file is being tracked
public:

    void viewTrackedFiles(Directory&);
    void viewUntrackedFiles(Directory&);
    void addFilesToStagingArea(string, Directory &);
    void copyToTrack(Directory &);
    vector<bool> & getTrack();
};

class Repository : public StagingArea, public Project
{
private:
    //files already committed
    vector<bool> committed; //boolean vector signifies which file is being committed
public:
    void viewFilesInRepos(Directory&);
    void addFilesToCommit(Directory&,Project&,StagingArea&);
    Repository &copyStagingToRepo(Directory&);
};
