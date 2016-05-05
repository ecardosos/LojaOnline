#include "Interfaces\Store\IUserDataManager.h"

#include <map>

class UserDataManager : public IUserDataManager
{
public:
  UserDataManager();
  ~UserDataManager();

  // Adds a new user.
  void addUser(IUser* newUser) override;

  // Returns an user with the given login.
  IUser* getUser(const char* login) override;

  // Sets the user that is currently logged into the system.
  // If user is nullptr, the user is logged out.
  void setCurrentUser(IUser* user) override;

  // Returns the user that is currently logged into the system.
  // Returns nullptr if no user is logged in.
  IUser* getCurrentUser() const override;

  // Forbidden methods.
  UserDataManager(const UserDataManager& m) = delete;
  void operator=(const UserDataManager& m)  = delete;

private:
  // Map associating an user id with its object.
  std::map<const char*, IUser*> _registeredUsers;

  IUser* _currentUser;
};