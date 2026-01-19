#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <map>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <limits>
#include <fstream>

using namespace std;

struct Date {
    int day, month, year;
    Date() : day(1), month(1), year(2025) {}
    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    string toString() const {
        stringstream ss;
        ss << setfill('0') << setw(2) << day << "/"
           << setw(2) << month << "/" << year;
        return ss.str();
    }

    bool operator<(const Date& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }

    bool operator==(const Date& other) const {
        return day == other.day && month == other.month && year == other.year;
    }
};

class Employee {
public:
    int id;
    string name;
    string department;
    string position;
    string email;

    Employee(int i, string n, string d, string p, string e)
        : id(i), name(n), department(d), position(p), email(e) {}
};

class Task {
public:
    int id;
    string title;
    string description;
    string assignedTo;
    Date deadline;
    int priority;
    string status;
    int projectId;
    int estimatedHours;

    Task(int i, string t, string desc, string assigned, Date d, int pri, int projId, int hours)
        : id(i), title(t), description(desc), assignedTo(assigned),
          deadline(d), priority(pri), status("Pending"), projectId(projId), estimatedHours(hours) {}

    bool operator<(const Task& other) const {
        if (priority != other.priority) return priority > other.priority;
        return deadline.operator<(other.deadline);
    }
};

class Project {
public:
    int id;
    string name;
    string description;
    Date startDate;
    Date endDate;
    string status;
    vector<int> taskIds;

    Project(int i, string n, string desc, Date start, Date end)
        : id(i), name(n), description(desc), startDate(start), endDate(end), status("Active") {}
};

class Announcement {
public:
    int id;
    string title;
    string content;
    Date date;
    string author;

    Announcement(int i, string t, string c, Date d, string a)
        : id(i), title(t), content(c), date(d), author(a) {}
};

class LeaveRequest {
public:
    int id;
    string employeeName;
    Date startDate;
    Date endDate;
    string reason;
    string status;

    LeaveRequest(int i, string emp, Date start, Date end, string r)
        : id(i), employeeName(emp), startDate(start), endDate(end),
          reason(r), status("Pending") {}
};

class Note {
public:
    int id;
    string content;
    Date createdDate;

    Note(int i, string c, Date d) : id(i), content(c), createdDate(d) {}
};

class ActivityLog {
public:
    string timestamp;
    string action;
    string user;

    ActivityLog(string ts, string act, string u)
        : timestamp(ts), action(act), user(u) {}
};

class Email {
public:
    int id;
    string from;
    string to;
    string subject;
    string body;
    Date sentDate;
    bool isRead;

    Email(int i, string f, string t, string s, string b, Date d)
        : id(i), from(f), to(t), subject(s), body(b), sentDate(d), isRead(false) {}
};

class TaskManagementSystem {
private:
    vector<Employee> employees;
    vector<Task> tasks;
    vector<Project> projects;
    vector<Announcement> announcements;
    vector<LeaveRequest> leaveRequests;
    vector<Note> personalNotes;
    vector<ActivityLog> activityLogs;
    vector<Email> emails;
    vector<string> chatMessages;
    map<string, string> userPreferences;

    int nextEmployeeId, nextTaskId, nextProjectId, nextAnnouncementId, nextLeaveId, nextNoteId, nextEmailId;
    string currentUser;
    string currentLanguage;

    void clearInputBuffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    void logActivity(string action) {
        time_t now = time(0);
        char* dt = ctime(&now);
        string timestamp(dt);
        if (!timestamp.empty() && timestamp[timestamp.length()-1] == '\n') {
            timestamp.erase(timestamp.length()-1);
        }
        activityLogs.push_back(ActivityLog(timestamp, action, currentUser));
    }

    bool askContinue(string message = "Add another") {
        char choice;
        cout << "\n" << message << "? (y/n): ";
        cin >> choice;
        cin.ignore();
        return (choice == 'y' || choice == 'Y');
    }

    void saveToFile() {
        string filename;
        cout << "\n=== Save Data to File ===\n";
        cout << "Enter filename (e.g., company_data.txt): ";
        getline(cin, filename);

        ofstream outFile(filename);
        if (!outFile.is_open()) {
            cout << "Error: Could not create file!\n";
            return;
        }

        outFile << "=== PROJECTS ===\n";
        outFile << projects.size() << "\n";
        for (size_t i = 0; i < projects.size(); i++) {
            outFile << projects[i].id << "|"
                   << projects[i].name << "|"
                   << projects[i].description << "|"
                   << projects[i].startDate.day << " " << projects[i].startDate.month << " " << projects[i].startDate.year << "|"
                   << projects[i].endDate.day << " " << projects[i].endDate.month << " " << projects[i].endDate.year << "|"
                   << projects[i].status << "\n";
        }

        outFile << "\n=== EMPLOYEES ===\n";
        outFile << employees.size() << "\n";
        for (size_t i = 0; i < employees.size(); i++) {
            outFile << employees[i].id << "|"
                   << employees[i].name << "|"
                   << employees[i].department << "|"
                   << employees[i].position << "|"
                   << employees[i].email << "\n";
        }

        outFile << "\n=== TASKS ===\n";
        outFile << tasks.size() << "\n";
        for (size_t i = 0; i < tasks.size(); i++) {
            outFile << tasks[i].id << "|"
                   << tasks[i].title << "|"
                   << tasks[i].description << "|"
                   << tasks[i].assignedTo << "|"
                   << tasks[i].deadline.day << " " << tasks[i].deadline.month << " " << tasks[i].deadline.year << "|"
                   << tasks[i].priority << "|"
                   << tasks[i].status << "|"
                   << tasks[i].projectId << "|"
                   << tasks[i].estimatedHours << "\n";
        }

        outFile << "\n=== ANNOUNCEMENTS ===\n";
        outFile << announcements.size() << "\n";
        for (size_t i = 0; i < announcements.size(); i++) {
            outFile << announcements[i].id << "|"
                   << announcements[i].title << "|"
                   << announcements[i].content << "|"
                   << announcements[i].date.day << " " << announcements[i].date.month << " " << announcements[i].date.year << "|"
                   << announcements[i].author << "\n";
        }

        outFile << "\n=== LEAVE REQUESTS ===\n";
        outFile << leaveRequests.size() << "\n";
        for (size_t i = 0; i < leaveRequests.size(); i++) {
            outFile << leaveRequests[i].id << "|"
                   << leaveRequests[i].employeeName << "|"
                   << leaveRequests[i].startDate.day << " " << leaveRequests[i].startDate.month << " " << leaveRequests[i].startDate.year << "|"
                   << leaveRequests[i].endDate.day << " " << leaveRequests[i].endDate.month << " " << leaveRequests[i].endDate.year << "|"
                   << leaveRequests[i].reason << "|"
                   << leaveRequests[i].status << "\n";
        }

        outFile << "\n=== ACTIVITY LOGS ===\n";
        outFile << activityLogs.size() << "\n";
        for (size_t i = 0; i < activityLogs.size(); i++) {
            outFile << activityLogs[i].timestamp << "|"
                   << activityLogs[i].action << "|"
                   << activityLogs[i].user << "\n";
        }

        outFile.close();
        cout << "\nData saved successfully to '" << filename << "'!\n";
        logActivity("Saved data to file: " + filename);
    }

    void loadFromFile() {
        string filename;
        cout << "\n=== Load Data from File ===\n";
        cout << "Enter filename to load: ";
        getline(cin, filename);

        ifstream inFile(filename);
        if (!inFile.is_open()) {
            cout << "Error: Could not open file!\n";
            return;
        }

        string line;
        int count;

        getline(inFile, line);
        inFile >> count;
        inFile.ignore();
        projects.clear();
        for (int i = 0; i < count; i++) {
            getline(inFile, line);
            stringstream ss(line);
            string token;
            int id, d, m, y;
            string name, desc, status;

            getline(ss, token, '|'); id = stoi(token);
            getline(ss, name, '|');
            getline(ss, desc, '|');
            getline(ss, token, '|');
            stringstream dateStream(token);
            dateStream >> d >> m >> y;
            Date startDate(d, m, y);
            getline(ss, token, '|');
            stringstream dateStream2(token);
            dateStream2 >> d >> m >> y;
            Date endDate(d, m, y);
            getline(ss, status, '|');

            Project p(id, name, desc, startDate, endDate);
            p.status = status;
            projects.push_back(p);
            if (id >= nextProjectId) nextProjectId = id + 1;
        }

        getline(inFile, line);
        getline(inFile, line);
        inFile >> count;
        inFile.ignore();
        employees.clear();
        for (int i = 0; i < count; i++) {
            getline(inFile, line);
            stringstream ss(line);
            string token;
            int id;
            string name, dept, pos, email;

            getline(ss, token, '|'); id = stoi(token);
            getline(ss, name, '|');
            getline(ss, dept, '|');
            getline(ss, pos, '|');
            getline(ss, email, '|');

            employees.push_back(Employee(id, name, dept, pos, email));
            if (id >= nextEmployeeId) nextEmployeeId = id + 1;
        }

        getline(inFile, line);
        getline(inFile, line);
        inFile >> count;
        inFile.ignore();
        tasks.clear();
        for (int i = 0; i < count; i++) {
            getline(inFile, line);
            stringstream ss(line);
            string token;
            int id, priority, projectId, hours, d, m, y;
            string title, desc, assigned, status;

            getline(ss, token, '|'); id = stoi(token);
            getline(ss, title, '|');
            getline(ss, desc, '|');
            getline(ss, assigned, '|');
            getline(ss, token, '|');
            stringstream dateStream(token);
            dateStream >> d >> m >> y;
            Date deadline(d, m, y);
            getline(ss, token, '|'); priority = stoi(token);
            getline(ss, status, '|');
            getline(ss, token, '|'); projectId = stoi(token);
            getline(ss, token, '|'); hours = stoi(token);

            Task t(id, title, desc, assigned, deadline, priority, projectId, hours);
            t.status = status;
            tasks.push_back(t);
            if (id >= nextTaskId) nextTaskId = id + 1;
        }

        getline(inFile, line);
        getline(inFile, line);
        inFile >> count;
        inFile.ignore();
        announcements.clear();
        for (int i = 0; i < count; i++) {
            getline(inFile, line);
            stringstream ss(line);
            string token;
            int id, d, m, y;
            string title, content, author;

            getline(ss, token, '|'); id = stoi(token);
            getline(ss, title, '|');
            getline(ss, content, '|');
            getline(ss, token, '|');
            stringstream dateStream(token);
            dateStream >> d >> m >> y;
            Date date(d, m, y);
            getline(ss, author, '|');

            announcements.push_back(Announcement(id, title, content, date, author));
            if (id >= nextAnnouncementId) nextAnnouncementId = id + 1;
        }

        getline(inFile, line);
        getline(inFile, line);
        inFile >> count;
        inFile.ignore();
        leaveRequests.clear();
        for (int i = 0; i < count; i++) {
            getline(inFile, line);
            stringstream ss(line);
            string token;
            int id, d1, m1, y1, d2, m2, y2;
            string empName, reason, status;

            getline(ss, token, '|'); id = stoi(token);
            getline(ss, empName, '|');
            getline(ss, token, '|');
            stringstream dateStream1(token);
            dateStream1 >> d1 >> m1 >> y1;
            Date startDate(d1, m1, y1);
            getline(ss, token, '|');
            stringstream dateStream2(token);
            dateStream2 >> d2 >> m2 >> y2;
            Date endDate(d2, m2, y2);
            getline(ss, reason, '|');
            getline(ss, status, '|');

            LeaveRequest lr(id, empName, startDate, endDate, reason);
            lr.status = status;
            leaveRequests.push_back(lr);
            if (id >= nextLeaveId) nextLeaveId = id + 1;
        }

        getline(inFile, line);
        getline(inFile, line);
        inFile >> count;
        inFile.ignore();
        activityLogs.clear();
        for (int i = 0; i < count; i++) {
            getline(inFile, line);
            stringstream ss(line);
            string timestamp, action, user;

            getline(ss, timestamp, '|');
            getline(ss, action, '|');
            getline(ss, user, '|');

            activityLogs.push_back(ActivityLog(timestamp, action, user));
        }

        inFile.close();
        cout << "\nData loaded successfully from '" << filename << "'!\n";
        cout << "Loaded: " << projects.size() << " projects, "
             << employees.size() << " employees, "
             << tasks.size() << " tasks\n";
        logActivity("Loaded data from file: " + filename);
    }

public:
    TaskManagementSystem() {
        nextEmployeeId = 1; nextTaskId = 1; nextProjectId = 1;
        nextAnnouncementId = 1; nextLeaveId = 1; nextNoteId = 1; nextEmailId = 1;
        currentUser = "Admin"; currentLanguage = "English";
    }

    void createProject() {
        bool continueAdding = true;
        while(continueAdding) {
            string name, desc; int d, m, y;
            cout << "\n=== Create New Project ===\n";
            cout << "Project Name: "; getline(cin, name);
            cout << "Description: "; getline(cin, desc);
            cout << "Start Date (DD MM YYYY): "; cin >> d >> m >> y; Date start(d,m,y);
            cout << "End Date (DD MM YYYY): "; cin >> d >> m >> y; Date end(d,m,y);
            cin.ignore();

            projects.push_back(Project(nextProjectId++, name, desc, start, end));
            cout << "\nProject created successfully! (ID: " << nextProjectId-1 << ")\n";
            logActivity("Created project: " + name);

            continueAdding = askContinue("Create another project");
        }
    }

    void viewProjects() {
        cout << "\n=== All Projects ===\n";
        if (projects.empty()) { cout << "No projects found.\n"; return; }

        for (size_t i=0;i<projects.size();i++){
            cout << "\nID: " << projects[i].id << " | Name: " << projects[i].name << "\n";
            cout << "Status: " << projects[i].status << "\n";
            cout << "Duration: " << projects[i].startDate.toString() << " to "
                 << projects[i].endDate.toString() << "\n";
            cout << "Description: " << projects[i].description << "\n";
            cout << "Tasks: " << projects[i].taskIds.size() << "\n";
            cout << "--------------------------------------------------\n";
        }
    }

    void updateProject() {
        int id;
        cout << "\nEnter Project ID to update: ";
        cin >> id;
        cin.ignore();

        bool found = false;
        for(size_t i=0; i<projects.size(); i++){
            if(projects[i].id == id){
                found = true;
                cout << "\n=== Update Project (ID: " << id << ") ===\n";
                cout << "Current Name: " << projects[i].name << "\n";
                cout << "New Name (press Enter to keep current): ";
                string name;
                getline(cin, name);
                if(!name.empty()) projects[i].name = name;

                cout << "Current Description: " << projects[i].description << "\n";
                cout << "New Description (press Enter to keep current): ";
                string desc;
                getline(cin, desc);
                if(!desc.empty()) projects[i].description = desc;

                cout << "Current Status: " << projects[i].status << "\n";
                cout << "New Status (Active/Completed/On Hold) (press Enter to keep current): ";
                string status;
                getline(cin, status);
                if(!status.empty()) projects[i].status = status;

                cout << "\nProject updated successfully!\n";
                logActivity("Updated project ID: " + to_string(id));
                break;
            }
        }
        if(!found) cout << "Project not found!\n";
    }

    void deleteProject() {
        bool continueDeleting = true;
        while(continueDeleting) {
            int id;
            cout << "\nEnter Project ID to delete: ";
            cin >> id;

            bool found = false;
            for(size_t i=0; i<projects.size(); i++){
                if(projects[i].id == id){
                    cout << "Are you sure you want to delete project '" << projects[i].name << "'? (y/n): ";
                    char confirm;
                    cin >> confirm;
                    if(confirm == 'y' || confirm == 'Y'){
                        string projectName = projects[i].name;
                        projects.erase(projects.begin() + i);
                        cout << "Project deleted successfully!\n";
                        logActivity("Deleted project: " + projectName);
                    } else {
                        cout << "Deletion cancelled.\n";
                    }
                    found = true;
                    break;
                }
            }
            if(!found) cout << "Project not found!\n";

            continueDeleting = askContinue("Delete another project");
        }
    }

    void scheduleTasksByDeadline() {
        cout << "\n=== Intelligent Task Scheduler ===\n";
        if (tasks.empty()) { cout << "No tasks to schedule.\n"; return; }

        vector<Task> sortedTasks = tasks;
        sort(sortedTasks.begin(), sortedTasks.end(),
             [](const Task& a,const Task& b){ return a.deadline < b.deadline; });

        cout << "\nRecommended Task Schedule:\n";
        for (size_t i=0;i<sortedTasks.size();i++)
            cout << i+1 << ". " << sortedTasks[i].title
                 << " (Deadline: " << sortedTasks[i].deadline.toString()
                 << ", Priority: " << sortedTasks[i].priority << ")\n";

        logActivity("Generated intelligent task schedule");
    }

    void optimizeWorkload() {
        cout << "\n=== Smart Workload Optimizer ===\n";
        if (tasks.empty()) { cout << "No tasks to optimize.\n"; return; }

        int availableHours; cout << "Enter available work hours: "; cin >> availableHours;
        int n = tasks.size();
        vector<vector<int>> dp(n+1, vector<int>(availableHours+1,0));

        for (int i=1;i<=n;i++){
            for (int w=0; w<=availableHours; w++){
                int hours = tasks[i-1].estimatedHours;
                int value = 4 - tasks[i-1].priority;
                if (hours <= w) dp[i][w] = max(dp[i-1][w], dp[i-1][w-hours]+value);
                else dp[i][w] = dp[i-1][w];
            }
        }

        vector<int> selectedTasks; int w = availableHours;
        for (int i=n;i>0 && w>0;i--){
            if (dp[i][w] != dp[i-1][w]){
                selectedTasks.push_back(i-1);
                w -= tasks[i-1].estimatedHours;
            }
        }

        cout << "\nOptimized Task Selection:\n"; int totalHours=0;
        for (size_t i=0;i<selectedTasks.size();i++){
            int idx = selectedTasks[i];
            cout << "- " << tasks[idx].title << " (" << tasks[idx].estimatedHours << " hours)\n";
            totalHours += tasks[idx].estimatedHours;
        }
        cout << "\nTotal Hours: " << totalHours << "/" << availableHours << "\n";
        cout << "Optimization Score: " << dp[n][availableHours] << "\n";

        logActivity("Optimized workload distribution");
    }

    void createTask() {
        bool continueAdding = true;
        while(continueAdding) {
            string title, desc, assigned; int priority, projectId, hours, d, m, y;
            cout << "\n=== Create New Task ===\n";
            cout << "Task Title: "; getline(cin,title);
            cout << "Description: "; getline(cin,desc);
            cout << "Assigned To: "; getline(cin,assigned);
            cout << "Deadline (DD MM YYYY): "; cin >> d >> m >> y; Date deadline(d,m,y);
            cout << "Priority (1=High,2=Med,3=Low): "; cin >> priority;
            cout << "Project ID: "; cin >> projectId;
            cout << "Estimated Hours: "; cin >> hours;
            cin.ignore();

            tasks.push_back(Task(nextTaskId++, title, desc, assigned, deadline, priority, projectId, hours));
            for (size_t i=0;i<projects.size();i++){
                if(projects[i].id==projectId) projects[i].taskIds.push_back(nextTaskId-1);
            }
            cout << "\nTask created successfully! (ID: " << nextTaskId-1 << ")\n";
            logActivity("Created task: " + title);

            continueAdding = askContinue("Create another task");
        }
    }

    void viewTasks() {
        cout << "\n=== All Tasks ===\n";
        if(tasks.empty()){ cout << "No tasks found.\n"; return; }

        for(size_t i=0;i<tasks.size();i++){
            cout << "\nID: " << tasks[i].id << " | " << tasks[i].title << "\n";
            cout << "Assigned to: " << tasks[i].assignedTo << "\n";
            cout << "Status: " << tasks[i].status << "\n";
            cout << "Priority: " << tasks[i].priority << " | Deadline: " << tasks[i].deadline.toString() << "\n";
            cout << "Estimated Hours: " << tasks[i].estimatedHours << "\n";
            cout << "--------------------------------------------------\n";
        }
    }

    void markTaskComplete() {
        bool continueMarking = true;
        while(continueMarking) {
            int id; cout << "\nEnter Task ID to mark complete: "; cin >> id;
            bool found = false;
            for(size_t i=0;i<tasks.size();i++){
                if(tasks[i].id==id){
                    tasks[i].status="Completed";
                    cout << "Task marked as completed!\n";
                    logActivity("Completed task ID: "+to_string(id));
                    found = true;
                    break;
                }
            }
            if(!found) cout << "Task not found!\n";

            continueMarking = askContinue("Mark another task complete");
        }
    }

    void updateTask() {
        int id;
        cout << "\nEnter Task ID to update: ";
        cin >> id;
        cin.ignore();

        bool found = false;
        for(size_t i=0; i<tasks.size(); i++){
            if(tasks[i].id == id){
                found = true;
                cout << "\n=== Update Task (ID: " << id << ") ===\n";
                cout << "Current Title: " << tasks[i].title << "\n";
                cout << "New Title (press Enter to keep current): ";
                string title;
                getline(cin, title);
                if(!title.empty()) tasks[i].title = title;

                cout << "Current Description: " << tasks[i].description << "\n";
                cout << "New Description (press Enter to keep current): ";
                string desc;
                getline(cin, desc);
                if(!desc.empty()) tasks[i].description = desc;

                cout << "Current Status: " << tasks[i].status << "\n";
                cout << "New Status (Pending/In Progress/Completed) (press Enter to keep current): ";
                string status;
                getline(cin, status);
                if(!status.empty()) tasks[i].status = status;

                cout << "Current Priority: " << tasks[i].priority << "\n";
                cout << "New Priority (1=High,2=Med,3=Low) (0 to keep current): ";
                int priority;
                cin >> priority;
                cin.ignore();
                if(priority >= 1 && priority <= 3) tasks[i].priority = priority;

                cout << "\nTask updated successfully!\n";
                logActivity("Updated task ID: " + to_string(id));
                break;
            }
        }
        if(!found) cout << "Task not found!\n";
    }

    void deleteTask() {
        bool continueDeleting = true;
        while(continueDeleting) {
            int id;
            cout << "\nEnter Task ID to delete: ";
            cin >> id;

            bool found = false;
            for(size_t i=0; i<tasks.size(); i++){
                if(tasks[i].id == id){
                    cout << "Are you sure you want to delete task '" << tasks[i].title << "'? (y/n): ";
                    char confirm;
                    cin >> confirm;
                    if(confirm == 'y' || confirm == 'Y'){
                        string taskTitle = tasks[i].title;
                        tasks.erase(tasks.begin() + i);
                        cout << "Task deleted successfully!\n";
                        logActivity("Deleted task: " + taskTitle);
                    } else {
                        cout << "Deletion cancelled.\n";
                    }
                    found = true;
                    break;
                }
            }
            if(!found) cout << "Task not found!\n";

            continueDeleting = askContinue("Delete another task");
        }
    }

    void mergeSortTasks(vector<Task>& arr,int left,int right){
        if(left>=right) return;
        int mid = left + (right-left)/2;
        mergeSortTasks(arr,left,mid);
        mergeSortTasks(arr,mid+1,right);

        vector<Task> temp; int i=left,j=mid+1;
        while(i<=mid && j<=right){
            if(arr[i].priority<=arr[j].priority) temp.push_back(arr[i++]);
            else temp.push_back(arr[j++]);
        }
        while(i<=mid) temp.push_back(arr[i++]);
        while(j<=right) temp.push_back(arr[j++]);
        for(size_t k=0;k<temp.size();k++) arr[left+k]=temp[k];
    }

    void sortTasksByPriority(){
        cout << "\n=== Priority-Based Task Organizer ===\n";
        if(tasks.empty()){ cout << "No tasks to sort.\n"; return; }
        vector<Task> sortedTasks=tasks;
        mergeSortTasks(sortedTasks,0,sortedTasks.size()-1);
        cout << "\nTasks organized by priority level:\n";
        for(size_t i=0;i<sortedTasks.size();i++){
            cout << "Priority " << sortedTasks[i].priority << ": " << sortedTasks[i].title << "\n";
        }
        logActivity("Organized tasks by priority");
    }

    void addEmployee(){
        bool continueAdding = true;
        while(continueAdding) {
            string name, dept, pos, email;
            cout << "\n=== Add New Employee ===\n";
            cout << "Name: "; getline(cin,name);
            cout << "Department: "; getline(cin,dept);
            cout << "Position: "; getline(cin,pos);
            cout << "Email: "; getline(cin,email);

            employees.push_back(Employee(nextEmployeeId++,name,dept,pos,email));
            cout << "\nEmployee added successfully! (ID: " << nextEmployeeId-1 << ")\n";
            logActivity("Added employee: "+name);

            continueAdding = askContinue("Add another employee");
        }
    }

    void viewEmployees(){
        cout << "\n=== All Employees ===\n";
        if(employees.empty()){ cout << "No employees found.\n"; return; }
        for(size_t i=0;i<employees.size();i++){
            cout << "\nID: " << employees[i].id << " | " << employees[i].name << "\n";
            cout << "Department: " << employees[i].department << " | Position: " << employees[i].position << "\n";
            cout << "Email: " << employees[i].email << "\n";
            cout << "--------------------------------------------------\n";
        }
    }

    void updateEmployee() {
        int id;
        cout << "\nEnter Employee ID to update: ";
        cin >> id;
        cin.ignore();

        bool found = false;
        for(size_t i=0; i<employees.size(); i++){
            if(employees[i].id == id){
                found = true;
                cout << "\n=== Update Employee (ID: " << id << ") ===\n";
                cout << "Current Name: " << employees[i].name << "\n";
                cout << "New Name (press Enter to keep current): ";
                string name;
                getline(cin, name);
                if(!name.empty()) employees[i].name = name;

                cout << "Current Department: " << employees[i].department << "\n";
                cout << "New Department (press Enter to keep current): ";
                string dept;
                getline(cin, dept);
                if(!dept.empty()) employees[i].department = dept;

                cout << "Current Position: " << employees[i].position << "\n";
                cout << "New Position (press Enter to keep current): ";
                string pos;
                getline(cin, pos);
                if(!pos.empty()) employees[i].position = pos;

                cout << "Current Email: " << employees[i].email << "\n";
                cout << "New Email (press Enter to keep current): ";
                string email;
                getline(cin, email);
                if(!email.empty()) employees[i].email = email;

                cout << "\nEmployee updated successfully!\n";
                logActivity("Updated employee ID: " + to_string(id));
                break;
            }
        }
        if(!found) cout << "Employee not found!\n";
    }

    void deleteEmployee() {
        bool continueDeleting = true;
        while(continueDeleting) {
            int id;
            cout << "\nEnter Employee ID to delete: ";
            cin >> id;

            bool found = false;
            for(size_t i=0; i<employees.size(); i++){
                if(employees[i].id == id){
                    cout << "Are you sure you want to delete employee '" << employees[i].name << "'? (y/n): ";
                    char confirm;
                    cin >> confirm;
                    if(confirm == 'y' || confirm == 'Y'){
                        string empName = employees[i].name;
                        employees.erase(employees.begin() + i);
                        cout << "Employee deleted successfully!\n";
                        logActivity("Deleted employee: " + empName);
                    } else {
                        cout << "Deletion cancelled.\n";
                    }
                    found = true;
                    break;
                }
            }
            if(!found) cout << "Employee not found!\n";

            continueDeleting = askContinue("Delete another employee");
        }
    }

    void createAnnouncement(){
        bool continueAdding = true;
        while(continueAdding) {
            string title, content; int d,m,y;
            cout << "\n=== Create Announcement ===\n";
            cout << "Title: "; getline(cin,title);
            cout << "Content: "; getline(cin,content);
            cout << "Date (DD MM YYYY): "; cin >> d >> m >> y;
            cin.ignore();

            announcements.push_back(Announcement(nextAnnouncementId++,title,content,Date(d,m,y),currentUser));
            cout << "\nAnnouncement created! (ID: " << nextAnnouncementId-1 << ")\n";
            logActivity("Created announcement: "+title);

            continueAdding = askContinue("Create another announcement");
        }
    }

    void viewAnnouncements(){
        cout << "\n=== Company Announcements ===\n";
        if(announcements.empty()){ cout << "No announcements.\n"; return; }
        for(size_t i=0;i<announcements.size();i++){
            cout << "\n[" << announcements[i].date.toString() << "] " << announcements[i].title << "\n";
            cout << "By: " << announcements[i].author << "\n";
            cout << announcements[i].content << "\n";
            cout << "--------------------------------------------------\n";
        }
    }

    void requestLeave(){
        bool continueAdding = true;
        while(continueAdding) {
            string empName, reason; int d1,m1,y1,d2,m2,y2;
            cout << "\n=== Request Leave ===\n";
            cout << "Employee Name: "; getline(cin,empName);
            cout << "Start Date (DD MM YYYY): "; cin >> d1 >> m1 >> y1;
            cout << "End Date (DD MM YYYY): "; cin >> d2 >> m2 >> y2;
            cin.ignore();
            cout << "Reason: "; getline(cin,reason);

            leaveRequests.push_back(LeaveRequest(nextLeaveId++,empName,Date(d1,m1,y1),Date(d2,m2,y2),reason));
            cout << "\nLeave request submitted! (ID: " << nextLeaveId-1 << ")\n";
            logActivity("Leave requested by: "+empName);

            continueAdding = askContinue("Submit another leave request");
        }
    }

    void viewLeaveRequests(){
        cout << "\n=== Leave Requests ===\n";
        if(leaveRequests.empty()){ cout << "No leave requests.\n"; return; }
        for(size_t i=0;i<leaveRequests.size();i++){
            cout << "\nID: " << leaveRequests[i].id << " | " << leaveRequests[i].employeeName << "\n";
            cout << "Period: " << leaveRequests[i].startDate.toString() << " to " << leaveRequests[i].endDate.toString() << "\n";
            cout << "Reason: " << leaveRequests[i].reason << "\n";
            cout << "Status: " << leaveRequests[i].status << "\n";
            cout << "--------------------------------------------------\n";
        }
    }

    void approveLeave(){
        bool continueApproving = true;
        while(continueApproving) {
            int id; cout << "\nEnter Leave Request ID to approve: "; cin >> id;
            bool found = false;
            for(size_t i=0;i<leaveRequests.size();i++){
                if(leaveRequests[i].id==id){
                    leaveRequests[i].status="Approved";
                    cout << "Leave approved!\n";
                    logActivity("Approved leave ID: "+to_string(id));
                    found = true;
                    break;
                }
            }
            if(!found) cout << "Leave request not found!\n";

            continueApproving = askContinue("Approve another leave request");
        }
    }

    void composeEmail() {
        bool continueComposing = true;
        while(continueComposing) {
            string to, subject, body;
            cout << "\n=== Compose Email ===\n";
            cout << "To (email address): "; getline(cin, to);

            bool validRecipient = false;
            for(size_t i=0; i<employees.size(); i++){
                if(employees[i].email == to){
                    validRecipient = true;
                    break;
                }
            }

            if(!validRecipient && to != "admin@company.com"){
                cout << "Warning: Recipient not found in employee directory.\n";
            }

            cout << "Subject: "; getline(cin, subject);
            cout << "Message Body: "; getline(cin, body);

            time_t now = time(0);
            tm* ltm = localtime(&now);
            Date today(ltm->tm_mday, 1+ltm->tm_mon, 1900+ltm->tm_year);

            emails.push_back(Email(nextEmailId++, currentUser+"@company.com", to, subject, body, today));
            cout << "\nEmail sent successfully! (ID: " << nextEmailId-1 << ")\n";
            logActivity("Sent email to: " + to);

            continueComposing = askContinue("Compose another email");
        }
    }

    void viewInbox() {
        cout << "\n=== Email Inbox ===\n";
        if(emails.empty()){ cout << "No emails found.\n"; return; }

        int unreadCount = 0;
        for(size_t i=0; i<emails.size(); i++){
            if(!emails[i].isRead) unreadCount++;

            cout << "\n" << (emails[i].isRead ? "[READ] " : "[UNREAD] ");
            cout << "ID: " << emails[i].id << " | From: " << emails[i].from << "\n";
            cout << "Subject: " << emails[i].subject << "\n";
            cout << "Date: " << emails[i].sentDate.toString() << "\n";
            cout << "--------------------------------------------------\n";
        }
        cout << "\nTotal: " << emails.size() << " emails (" << unreadCount << " unread)\n";
    }

    void readEmail() {
        int id;
        cout << "\nEnter Email ID to read: ";
        cin >> id;
        cin.ignore();

        bool found = false;
        for(size_t i=0; i<emails.size(); i++){
            if(emails[i].id == id){
                emails[i].isRead = true;
                cout << "\n========== EMAIL ==========\n";
                cout << "From: " << emails[i].from << "\n";
                cout << "To: " << emails[i].to << "\n";
                cout << "Subject: " << emails[i].subject << "\n";
                cout << "Date: " << emails[i].sentDate.toString() << "\n";
                cout << "---------------------------\n";
                cout << emails[i].body << "\n";
                cout << "===========================\n";
                found = true;
                logActivity("Read email ID: " + to_string(id));
                break;
            }
        }
        if(!found) cout << "Email not found!\n";
    }

    void addNote(){
        bool continueAdding = true;
        while(continueAdding) {
            string content;
            cout << "\n=== Add Personal Note ===\n";
            cout << "Note: "; getline(cin,content);

            time_t now=time(0); tm* ltm=localtime(&now);
            Date today(ltm->tm_mday,1+ltm->tm_mon,1900+ltm->tm_year);
            personalNotes.push_back(Note(nextNoteId++,content,today));
            cout << "\nNote saved! (ID: " << nextNoteId-1 << ")\n";
            logActivity("Added personal note");

            continueAdding = askContinue("Add another note");
        }
    }

    void viewNotes(){
        cout << "\n=== Your Personal Notes ===\n";
        if(personalNotes.empty()){ cout << "No notes found.\n"; return; }
        for(size_t i=0;i<personalNotes.size();i++){
            cout << "\n[" << personalNotes[i].createdDate.toString() << "] " << personalNotes[i].content << "\n";
        }
    }

    void chat(){
        string message; cout << "\n=== Personal Chat (Type 'exit' to quit) ===\n";
        while(true){
            cout << currentUser << ": "; getline(cin,message);
            if(message=="exit") break;
            chatMessages.push_back(currentUser+": "+message);
            cout << "System: Message received!\n";
        }
        logActivity("Used chat feature");
    }

    void setLanguage(){
        int choice; cout << "\n=== Language Settings ===\n";
        cout << "1. English\n2. Spanish\n3. French\n4. German\n"; cout << "Choose language: "; cin >> choice;
        switch(choice){ case 1: currentLanguage="English"; break;
            case 2: currentLanguage="Spanish"; break;
            case 3: currentLanguage="French"; break;
            case 4: currentLanguage="German"; break;
            default: cout << "Invalid choice!\n"; return;
        }
        userPreferences["language"]=currentLanguage;
        cout << "Language set to " << currentLanguage << "\n";
        logActivity("Changed language to: "+currentLanguage);
    }

    void setUserPreferences(){
        bool continueAdding = true;
        while(continueAdding) {
            string key,value;
            cout << "\n=== Set User Preference ===\n";
            cout << "Preference Key: "; getline(cin,key);
            cout << "Value: "; getline(cin,value);
            userPreferences[key]=value;
            cout << "\nPreference saved!\n";
            logActivity("Updated preference: "+key);

            continueAdding = askContinue("Set another preference");
        }
    }

    void viewActivityLog(){
        cout << "\n=== Activity Log ===\n";
        if(activityLogs.empty()){ cout << "No activity recorded.\n"; return; }
        for(size_t i=0;i<activityLogs.size();i++){
            cout << "[" << activityLogs[i].timestamp << "] " << activityLogs[i].user << ": " << activityLogs[i].action << "\n";
        }
    }

    void generateReport(){
        cout << "\n========== COMPANY REPORT ==========\n";
        cout << "Total Projects: " << projects.size() << "\n";
        cout << "Total Tasks: " << tasks.size() << "\n";
        cout << "Total Employees: " << employees.size() << "\n";
        int pending=0; for(size_t i=0;i<leaveRequests.size();i++) if(leaveRequests[i].status=="Pending") pending++;
        cout << "Pending Leave Requests: " << pending << "\n";

        int pendingTasks=0,inProgress=0,completed=0;
        for(size_t i=0;i<tasks.size();i++){
            if(tasks[i].status=="Pending") pendingTasks++;
            else if(tasks[i].status=="In Progress") inProgress++;
            else if(tasks[i].status=="Completed") completed++;
        }
        cout << "Task Status Breakdown:\n  Pending: " << pendingTasks << "\n  In Progress: " << inProgress << "\n  Completed: " << completed << "\n";

        int unreadEmails = 0;
        for(size_t i=0; i<emails.size(); i++) if(!emails[i].isRead) unreadEmails++;
        cout << "Total Emails: " << emails.size() << " (" << unreadEmails << " unread)\n";

        cout << "Recent Activities: " << activityLogs.size() << " logged\n";
        cout << "====================================\n";
        logActivity("Generated company report");
    }

    void displayMenu(){
        cout << "\n1.  Project Management\n2.  Task Management\n3.  Employee Management\n4.  Announcements\n";
        cout << "5.  Leave Management\n6.  Email Center\n7.  Personal Notes & To-Do\n8.  Chat\n9.  Reports\n";
        cout << "10. Activity Log\n11. Settings\n12. Task Analytics\n";
        cout << "13. Save Data to File\n14. Load Data from File\n0.  Exit\n";
        cout << "\nChoose an option: ";
    }

    void run(){
        int choice;
        while(true){
            displayMenu(); cin >> choice;
            if(cin.fail()){ clearInputBuffer(); cout << "\nInvalid input!\n"; continue; }
            clearInputBuffer();

            switch(choice){
                case 1: { int sub; cout << "\n1. Create Project\n2. View Projects\n3. Update Project\n4. Delete Project\nChoose: "; cin>>sub;
                    clearInputBuffer();
                    if(sub==1) createProject();
                    else if(sub==2) viewProjects();
                    else if(sub==3) updateProject();
                    else if(sub==4) deleteProject();
                    break;
                }
                case 2: { int sub; cout << "\n1. Create Task\n2. View Tasks\n3. Mark Complete\n4. Update Task\n5. Delete Task\nChoose: "; cin>>sub;
                    clearInputBuffer();
                    if(sub==1) createTask();
                    else if(sub==2) viewTasks();
                    else if(sub==3) markTaskComplete();
                    else if(sub==4) updateTask();
                    else if(sub==5) deleteTask();
                    break;
                }
                case 3: { int sub; cout << "\n1. Add Employee\n2. View Employees\n3. Update Employee\n4. Delete Employee\nChoose: "; cin>>sub;
                    clearInputBuffer();
                    if(sub==1) addEmployee();
                    else if(sub==2) viewEmployees();
                    else if(sub==3) updateEmployee();
                    else if(sub==4) deleteEmployee();
                    break;
                }
                case 4: { int sub; cout << "\n1. Create Announcement\n2. View Announcements\nChoose: "; cin>>sub;
                    clearInputBuffer();
                    if(sub==1) createAnnouncement(); else if(sub==2) viewAnnouncements(); break;
                }
                case 5: { int sub; cout << "\n1. Request Leave\n2. View Leave Requests\n3. Approve Leave\nChoose: "; cin>>sub;
                    clearInputBuffer();
                    if(sub==1) requestLeave(); else if(sub==2) viewLeaveRequests(); else if(sub==3) approveLeave(); break;
                }
                case 6: { int sub; cout << "\n1. Compose Email\n2. View Inbox\n3. Read Email\nChoose: "; cin>>sub;
                    clearInputBuffer();
                    if(sub==1) composeEmail(); else if(sub==2) viewInbox(); else if(sub==3) readEmail(); break;
                }
                case 7: { int sub; cout << "\n1. Add Note\n2. View Notes\nChoose: "; cin>>sub;
                    clearInputBuffer();
                    if(sub==1) addNote(); else if(sub==2) viewNotes(); break;
                }
                case 8: chat(); break;
                case 9: generateReport(); break;
                case 10: viewActivityLog(); break;
                case 11: { int sub; cout << "\n1. Set Language\n2. Set Custom Preference\nChoose: "; cin>>sub;
                    clearInputBuffer();
                    if(sub==1) setLanguage(); else if(sub==2) setUserPreferences(); break;
                }
                case 12: { int sub; cout << "\n=== Task Analytics ===\n1. Intelligent Task Scheduler \n2. Priority-Based Task Organizer\nChoose: "; cin>>sub;
                    if(sub==1) scheduleTasksByDeadline(); else if(sub==2) optimizeWorkload(); else if(sub==3) sortTasksByPriority(); break;
                }
                case 13: saveToFile(); break;
                case 14: loadFromFile(); break;
                case 0: cout<<"\nThank you for using the system!\n"; return;
                default: cout<<"\nInvalid choice! Try again.\n";
            }
        }
    }
};

int main() {
    TaskManagementSystem system;

    cout << "===============================================\n";
    cout << "   SMART COMPANY TASK MANAGEMENT SYSTEM        \n";
    cout << "===============================================\n\n";

    system.run();
    return 0;
}

