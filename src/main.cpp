#include <iostream>
#include <mysql.h>
#include <mysqld_error.h>
#include <windows.h>
using namespace std;

const char* HOST = "localhost";
const char* USER = "root";
const char* PW = "password";
const char* DB = "BloodBankDB";

int main() {
    MYSQL* conn;
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, HOST, USER, PW, DB, 3306, NULL, 0)) {
        cout << endl << endl;
        cout << "\t\t Error: " << mysql_error(conn) << endl;
    }
    else {
        cout << endl << endl;
        cout << "\t\t Logged in to Blood Bank DB!" << endl;
    }

    Sleep(3000);
    bool exit = false;
    while (!exit) {
        system("cls");
        int val;
        cout << endl << endl;
        cout << "\t\t BLOOD BANK MANAGEMENT SYSTEM" << endl;
        cout << "\t\t ****************************" << endl;
        cout << "\t\t 1. Insert Donor Data" << endl;
        cout << "\t\t 2. Delete Donor Data" << endl;
        cout << "\t\t 3. Update Donor Contact" << endl;
        cout << "\t\t 4. View All Donors" << endl;
        cout << "\t\t 0. Exit" << endl;
        cout << "\t\t Enter Choice: ";
        cin >> val;

        if (val == 1) {
            system("cls");
            string fname, lname, gender, dob, bloodgroup, disease, contact, email, address, regdate;
            cout << endl << "\t\t Enter First Name: ";
            cin >> fname;
            cout << "\t\t Enter Last Name: ";
            cin >> lname;
            cout << "\t\t Enter Gender (M/F): ";
            cin >> gender;
            cout << "\t\t Enter DOB (YYYY-MM-DD): ";
            cin >> dob;
            cout << "\t\t Enter Blood Group (A+/O-/...): ";
            cin >> bloodgroup;
            cout << "\t\t Enter Disease Status: ";
            cin >> disease;
            cout << "\t\t Enter Contact Number: ";
            cin >> contact;
            cout << "\t\t Enter Email: ";
            cin >> email;
            cout << "\t\t Enter Address: ";
            cin.ignore();
            getline(cin, address);
            cout << "\t\t Enter Registration Date (YYYY-MM-DD): ";
            cin >> regdate;

            string ins = "INSERT INTO Donor (FirstName, LastName, Gender, DateOfBirth, BloodGroup, DiseaseStatus, ContactNumber, Email, Address, RegistrationDate) "
                         "VALUES('" + fname + "', '" + lname + "', '" + gender + "', '" + dob + "', '" + bloodgroup + "', '" + disease + "', '" + contact + "', '" + email + "', '" + address + "', '" + regdate + "')";
            
            if (mysql_query(conn, ins.c_str())) {
                cout << endl << "\t\t Error: " << mysql_error(conn) << endl;
            }
            else {
                cout << endl << "\t\t Donor inserted successfully!" << endl;
            }
            Sleep(3000);
        }
        else if (val == 2) {
            system("cls");
            string id;
            cout << "\t\t Enter Donor ID to Delete: ";
            cin >> id;

            string del = "DELETE FROM Donor WHERE DonorID = '" + id + "'";
            if (mysql_query(conn, del.c_str())) {
                cout << endl << "\t\t Error: " << mysql_error(conn) << endl;
            }
            else {
                cout << endl << "\t\t Donor Deleted Successfully" << endl;
            }
            Sleep(3000);
        }
        else if (val == 3) {
            system("cls");
            string id, newContact;
            cout << "\t\t Enter Donor ID to Update: ";
            cin >> id;
            cout << "\t\t Enter New Contact Number: ";
            cin >> newContact;

            string upd = "UPDATE Donor SET ContactNumber = '" + newContact + "' WHERE DonorID = '" + id + "'";
            if (mysql_query(conn, upd.c_str())) {
                cout << endl << "\t\t Error: " << mysql_error(conn) << endl;
            }
            else {
                cout << endl << "\t\t Contact Updated Successfully" << endl;
            }
            Sleep(3000);
        }
        else if (val == 4) {
            system("cls");
            string get = "SELECT DonorID, FirstName, LastName, BloodGroup, ContactNumber FROM Donor";
            if (mysql_query(conn, get.c_str())) {
                cout << endl << "\t\t Error: " << mysql_error(conn) << endl;
            }
            else {
                MYSQL_RES* result = mysql_store_result(conn);
                if (result) {
                    int num = mysql_num_fields(result);
                    MYSQL_ROW row;
                    cout << endl << "\t\t ID\t Name\t Blood Group\t Contact" << endl;
                    cout << "\t\t --\t ----\t ------------\t --------" << endl;
                    while ((row = mysql_fetch_row(result))) {
                        for (int i = 0; i < num; i++) {
                            cout << "\t\t " << row[i];
                        }
                        cout << endl;
                    }
                    mysql_free_result(result);
                }
            }
            Sleep(10000);
        }
        else if (val == 0) {
            system("cls");
            exit = true;
            cout << endl << "\t\t Exiting Blood Bank System..." << endl;
            Sleep(3000);
        }
        else {
            cout << endl << "\t\t Invalid Input!" << endl;
            Sleep(3000);
        }
    }

    mysql_close(conn);
    return 0;
}
