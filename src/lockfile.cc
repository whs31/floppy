#include <rll/lockfile.h>

#include <fstream>

namespace rll {
  lockfile::lockfile(std::filesystem::path const& path)
    : locked_(false)
    , path_(path) {}

  lockfile::lockfile(std::filesystem::path&& path)
    : locked_(false)
    , path_(std::move(path)) {}

  std::filesystem::path const& lockfile::path() const noexcept { return this->path_; }

  bool lockfile::is_locked() const noexcept { return this->locked_; }

  bool lockfile::try_lock() noexcept {
    if(this->locked_)
      return false;
    try {
      this->lock();
    } catch(...) {
      return false;
    }
    return true;
  }

  void lockfile::lock() {
    try {
      auto ec = std::error_code();
      create_directories(this->path_.parent_path(), ec);
      auto ofs = std::ofstream(this->path_);
      ofs << "locked";
      ofs.close();
      this->locked_ = true;
    } catch(...) {
      this->unlock();
      throw;
    }
  }

  void lockfile::unlock() noexcept {
    auto ec = std::error_code();
    remove(this->path_, ec);
    this->locked_ = false;
  }
}  // namespace rll
