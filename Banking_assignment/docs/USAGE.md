# Usage Guide — Banking Application Simulator

This guide walks through every user-facing flow of the application with annotated sample terminal sessions.

---

## Table of Contents

1. [Starting the Application](#starting-the-application)
2. [Admin Flows](#admin-flows)
   - [Logging in as Admin](#logging-in-as-admin)
   - [Registering a Customer](#registering-a-customer)
   - [Viewing All Customers](#viewing-all-customers)
   - [Viewing All Accounts](#viewing-all-accounts)
   - [Searching by Account Number](#searching-by-account-number)
   - [Editing Customer Details](#editing-customer-details)
   - [Managing a Customer's Account](#managing-a-customers-account)
   - [Deleting a Customer](#deleting-a-customer)
   - [Logging out as Admin](#logging-out-as-admin)
3. [Customer Flows](#customer-flows)
   - [Logging in as Customer](#logging-in-as-customer)
   - [Depositing Funds](#depositing-funds)
   - [Withdrawing Funds](#withdrawing-funds)
   - [Checking Balance](#checking-balance)
   - [Changing PIN](#changing-pin)
   - [Viewing Mini Statement](#viewing-mini-statement)
   - [Viewing Full Bank Statement](#viewing-full-bank-statement)
4. [Security Notes](#security-notes)
5. [Error Handling Reference](#error-handling-reference)

---

## Starting the Application

```
$ ./build/BankAppSimulator

=============== WELCOME ===============
1. Login as an Admin
2. Login as a Customer
3. Exit
========================================

Enter your choice:
```

Enter `1` for the admin flow, `2` for the customer flow, or `3` to exit.

---

## Admin Flows

### Logging in as Admin

```
Enter your choice: 1

===== ADMIN LOGIN =====
Enter username: hiya
Enter password: system

Login successful!
```

Default credentials: **username** `hiya`, **password** `system`.

After 3 consecutive failed attempts the session is locked and you are returned to the main menu:

```
Login failed! Incorrect credentials.
Attempts remaining: 2
...
Access denied! Maximum login attempts exceeded.
```

---

### Registering a Customer

From the admin menu, enter `1`:

```
=============== ADMIN OPERATIONS ===============
1. Register Customer
...
Enter your choice: 1

===== REGISTER NEW CUSTOMER =====
Customer Name: Daksh Sharma
Customer Email: daksh@gmail.com
Customer Phone Number: 9876543210

Account Number: 10000000
PIN: 4271

Customer registered successfully!
```

> The account number increments by 1 for each new registration. The PIN is randomly generated.  
> **Important:** Note down the account number and PIN — they are only displayed once.

---

### Viewing All Customers

```
Enter your choice: 2

===== LIST OF ALL CUSTOMERS =====
Total Customers: 2

Customer Name: Daksh Sharma
Email: daksh@gmail.com
Phone: 9876543210
Account Number: 10000000
----------------------------

Customer Name: Priya Verma
Email: priya@example.com
Phone: 8765432109
Account Number: 10000001
----------------------------
```

---

### Viewing All Accounts

```
Enter your choice: 3

===== LIST OF ALL ACCOUNTS =====
Total Accounts: 2

Account Number: 10000000
Balance: 5000.00
----------------------------

Account Number: 10000001
Balance: 0.00
----------------------------
```

---

### Searching by Account Number

**Search customer:**
```
Enter your choice: 4

===== SEARCH CUSTOMER BY ACCOUNT =====
Enter account number: 10000000

Customer Found!

Customer Name: Daksh Sharma
Email: daksh@gmail.com
Phone: 9876543210
Account Number: 10000000
```

**Search account:**
```
Enter your choice: 5

===== SEARCH ACCOUNT BY NUMBER =====
Enter account number: 10000000

Account Found!

Account Number: 10000000
Balance: 5000.00
```

If the account does not exist:
```
No customer found with account number: 99999999
```

---

### Editing Customer Details

```
Enter your choice: 6

===== EDIT CUSTOMER DETAILS =====
Enter account number: 10000000

Current Details:
Customer Name: Daksh Sharma
Email: daksh@gmail.com
Phone: 9876543210
Account Number: 10000000

--- What would you like to edit? ---
1. Name
2. Email
3. Phone
4. PIN
5. Cancel
Enter choice: 2

Enter new email: daksh.sharma@gmail.com
Email updated!
```

---

### Managing a Customer's Account

Allows the admin to deposit, withdraw, or check balance on behalf of a customer:

```
Enter your choice: 7

===== MANAGE CUSTOMER ACCOUNT =====
Enter account number: 10000000

1. Deposit
2. Withdraw
3. Check Balance
4. Cancel
Enter choice: 1

Transaction amount must be between 100-10000.
Enter the amount you want to deposit: 2000

Deposited Money! Balance after transaction: 7000.00
```

---

### Deleting a Customer

A customer can only be deleted when their account balance is exactly zero:

```
Enter your choice: 8

===== DELETE CUSTOMER =====
Enter Account Number of customer to delete: 10000001

Customer Deleted Successfully!
```

If the customer has a remaining balance:
```
Cannot delete customer with remaining balance: 5000.00
Please withdraw all funds before deletion.
```

---

### Logging out as Admin

```
Enter your choice: 9
[screen cleared]
Logged out successfully!
```

---

## Customer Flows

### Logging in as Customer

```
Enter your choice: 2

===== CUSTOMER LOGIN =====
Enter account number: 10000000
Enter PIN: 4271

Login successful!
```

If the account number does not exist:
```
This account number does not exist. Please visit your nearest branch to open a new account.
```

After 3 PIN failures the session is locked:
```
Login failed! Incorrect credentials.
Attempts remaining: 1
...
Access denied! Maximum login attempts exceeded.
```

---

### Depositing Funds

From the customer menu, enter `1`:

```
=============== CUSTOMER OPERATIONS ===============
1. Deposit
...
Enter your choice: 1

Transaction amount must be between 100-10000.
Enter the amount you want to deposit: 500

Deposited Money! Balance after transaction: 500.00
```

Amounts outside the range `[100, 10000]` are rejected:
```
Enter the amount you want to deposit: 50
Deposit failed. Entered amount is not in range.
```

---

### Withdrawing Funds

```
Enter your choice: 2

Transaction amount must be between 100-10000.
Enter the amount you want to withdraw: 200

Withdrawn Money! Balance after transaction: 300.00
```

If funds are insufficient:
```
You do not have enough balance for this!
```

---

### Checking Balance

```
Enter your choice: 3

Your current balance is: 300.00
```

---

### Changing PIN

```
Enter your choice: 4

Enter old PIN: 4271
Enter new PIN (4 digits): 8842
Re-enter your PIN: 8842
PIN updated!.
You are getting logged out. Kindly login again!
```

> Changing the PIN immediately ends the session. The customer must log in again with the new PIN.

If the old PIN is incorrect:
```
Entered PIN is incorrect.
If you have forgot the pin, kindly contact your bank
```

If the two new PINs do not match:
```
PINS do not match. Try again!
```

---

### Viewing Mini Statement

Shows the most recent 5 transactions:

```
Enter your choice: 5

========== Mini Statement (Last 5 Transactions) ==========
   ID        Type    Amount    Post Balance
    1     Deposit    500.00         500.00
    2  Withdrawal    200.00         300.00
    3     Deposit   1000.00        1300.00
===========================================================
```

---

### Viewing Full Bank Statement

Shows the complete transaction history:

```
Enter your choice: 6

================== Full Bank Statement ===================
   ID        Type    Amount    Post Balance
    1     Deposit    500.00         500.00
    2  Withdrawal    200.00         300.00
    3     Deposit   1000.00        1300.00
    4  Withdrawal    100.00        1200.00
===========================================================
```

If no transactions have been made:
```
No transactions found.
```

---

## Security Notes

| Topic | Current Behaviour | Production Recommendation |
|---|---|---|
| Admin credentials | Stored as plaintext in `Constants.h` | Store as salted SHA-256 hash loaded from a config file at startup |
| Customer PIN | Stored as plaintext string in `Account` | Hash with bcrypt or Argon2 before storage |
| Session lockout | 3 failed attempts → return to main menu | Implement a timed cooldown or permanent lockout with audit logging |
| PIN display | Shown once at registration | Deliver via a secure out-of-band channel (SMS / email) |

---

## Error Handling Reference

| Scenario | Message shown |
|---|---|
| Non-numeric input where a number is expected | `Invalid Input. Please enter a number:` |
| Empty string submitted | `Input cannot be empty! Enter again:` |
| Name shorter than 3 characters | `Invalid Input. Name should be at least 3 characters!` |
| Name contains non-alpha/non-space characters | `Invalid Input. Only alphabets and spaces expected!` |
| Malformed email | Context-specific message (missing @, missing domain, etc.) |
| Phone number not exactly 10 digits | `Invalid Input. Input should be exactly 10 digits!` |
| PIN not exactly 4 digits | `Invalid Input. Input should be exactly 4 digits!` |
| Account number not exactly 8 digits | `Invalid Input. Input should be exactly 8 digits!` |
| Transaction amount out of range | `Deposit/Withdrawal failed. Entered amount is not in range.` |
| Insufficient balance | `You do not have enough balance for this!` |
| Account not found | `This account number does not exist.` |
| Customer not found by account | `No customer found with account number: <number>` |
| Delete with non-zero balance | `Cannot delete customer with remaining balance: <amount>` |
| Max login attempts exceeded | `Access denied! Maximum login attempts exceeded.` |
