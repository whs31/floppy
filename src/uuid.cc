#include <rll/uuid.h>

#include <cstring>
#include <iomanip>
#include <iostream>

#include <limits>
#include <random>

namespace rll {
  uuid::uuid(std::array<std::byte, 16> const& bytes) {  // NOLINT(*-pro-type-member-init)
    std::memcpy(this->bytes_.data(), bytes.data(), 16);
  }

  std::string uuid::to_string() const {
    return fmt::format(
      "{:02x}{:02x}{:02x}{:02x}-{:02x}{:02x}-{:02x}{:02x}-{:02x}{:02x}-{:02x}{:02x}{:02x}{:02x}{:"
      "02x}{:02x}",
      this->bytes_[0],
      this->bytes_[1],
      this->bytes_[2],
      this->bytes_[3],
      this->bytes_[4],
      this->bytes_[5],
      this->bytes_[6],
      this->bytes_[7],
      this->bytes_[8],
      this->bytes_[9],
      this->bytes_[10],
      this->bytes_[11],
      this->bytes_[12],
      this->bytes_[13],
      this->bytes_[14],
      this->bytes_[15]
    );
  }

  std::ostream& operator<<(std::ostream& os, uuid const& guid) {
    auto flags = os.flags();
    os << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(guid.bytes()[0])
       << std::setw(2) << static_cast<int>(guid.bytes()[1]) << std::setw(2)
       << static_cast<int>(guid.bytes()[2]) << std::setw(2) << static_cast<int>(guid.bytes()[3])
       << "-" << std::setw(2) << static_cast<int>(guid.bytes()[4]) << std::setw(2)
       << static_cast<int>(guid.bytes()[5]) << "-" << std::setw(2)
       << static_cast<int>(guid.bytes()[6]) << std::setw(2) << static_cast<int>(guid.bytes()[7])
       << "-" << std::setw(2) << static_cast<int>(guid.bytes()[8]) << std::setw(2)
       << static_cast<int>(guid.bytes()[9]) << "-" << std::setw(2)
       << static_cast<int>(guid.bytes()[10]) << std::setw(2) << static_cast<int>(guid.bytes()[11])
       << std::setw(2) << static_cast<int>(guid.bytes()[12]) << std::setw(2)
       << static_cast<int>(guid.bytes()[13]) << std::setw(2) << static_cast<int>(guid.bytes()[14])
       << std::setw(2) << static_cast<int>(guid.bytes()[15]);
    os.flags(flags);
    return os;
  }

  uuid uuid::random() noexcept {
    thread_local auto engine = std::default_random_engine {std::random_device {}()};
    auto distribution = std::uniform_int_distribution<u32>(
      std::numeric_limits<u32>::min(),
      std::numeric_limits<u32>::max()
    );
    auto i = 0;
    auto random_value = distribution(engine);
    auto data = std::array<u8, 16> {};
    for(auto it = data.begin(); it != data.end(); ++it, ++i) {
      if(i == sizeof(u32)) {
        random_value = distribution(engine);
        i = 0;
      }
      *it = static_cast<u8>((random_value >> (i * 8)) & 0xFF);
    }
    *(data.begin() + 8) &= 0xBF;
    *(data.begin() + 8) |= 0x80;
    *(data.begin() + 6) &= 0x4F;
    *(data.begin() + 6) |= 0x40;
    return uuid(data);
  }

  result<uuid> uuid::try_parse(std::string_view const str) noexcept {
    try {
      return uuid(str);
    } catch(std::exception const& e) {
      return error("{}", e.what());
    }
  }

  u64 uuid::to_u64() const noexcept {
    return detail::hash<rll::u64, rll::u64> {}(bytes()[0], bytes()[1]);
  }
}  // namespace rll
