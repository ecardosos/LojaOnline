#include "Store\UserDataManager.h"

#include "Data\User.h"

UserDataManager::UserDataManager()
{

}

UserDataManager::~UserDataManager()
{
  _registeredUsers.clear();
}

void UserDataManager::addUser(IUser* newUser)
{
  if (newUser != nullptr)
  {
    _registeredUsers.insert(std::pair<const char*, IUser*>(newUser->getLogin(), newUser));
  }
}

IUser* UserDataManager::getUser(const char* login)
{
  // std::map::at throws a std::out_of_range exception if the element could not be found.
  // Therefore, return a nullptr if an exception is caught.
  try
  {
    if (login != nullptr)
    {
      return _registeredUsers.at(login);
    }

    return nullptr;
  }
  catch (...)
  {
    return nullptr;
  }
}

void UserDataManager::setCurrentUser(IUser* user)
{
  _currentUser = user;
}

IUser* UserDataManager::getCurrentUser() const
{
  return _currentUser;
}