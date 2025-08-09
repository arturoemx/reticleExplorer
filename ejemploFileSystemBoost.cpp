#include <iostream>
#include <boost/filesystem.hpp>

using namespace boost::filesystem;
using namespace std;

int main(int argc, char* argv[])
{
  std::string p(argc <= 1 ? "." : argv[1]);

  if (is_directory(p))
  {
    for (directory_iterator itr(p); itr!=directory_iterator(); ++itr)
    {
      cout << itr->path().filename() << ' '; // display filename only
      if (is_regular_file(itr->status())) cout << " [" << file_size(itr->path()) << ']';
      cout << '\n';
    }
  }
  else cout << (exists(p) ? "Found: " : "Not found: ") << p << '\n';

  return 0;
}