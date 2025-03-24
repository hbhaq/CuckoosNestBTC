#ifndef CUCKOO_FILTER_PRINTUTIL_H_
#define CUCKOO_FILTER_PRINTUTIL_H_

#include <string>

namespace cuckoofilter {
class PrintUtil {
 public:
  static std::string bytes_to_hex(const char* string, unsigned long i);
  static std::string bytes_to_hex(const std::string &s) {
    return bytes_to_hex((const char *)s.data(), s.size());
  }

 private:
 PrintUtil();
};  // class PrintUtil

}  // namespace cuckoofilter

#endif  // CUCKOO_FILTER_PRINTUTIL_H_
