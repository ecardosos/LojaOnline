#pragma once

class IUser;

class IUserDataManager
{
public:
  virtual ~IUserDataManager() {}

  // Adds a new user.
  virtual void addUser(IUser* newUser) = 0;

  // Returns an user with the given login.
  virtual IUser* getUser(const char* login) = 0;

  // Sets the user that is currently logged into the system.
  // If user is nullptr, the user is logged out.
  virtual void setCurrentUser(IUser* user) = 0;

  // Returns the user that is currently logged into the system.
  // Returns nullptr if no user is logged in.
  virtual IUser* getCurrentUser() const = 0;
};