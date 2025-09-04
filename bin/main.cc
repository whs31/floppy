#include <rll/all.h>
#include <fmt/chrono.h>

int main(int /*argc*/, char** /*argv*/) {
  using namespace rll;
  using namespace std::literals;

  auto lf1 = lockfile("test.lock");
  auto lf = std::scoped_lock(lf1);

  auto ip = "127.0.0.1"_ipv4;
  assert_precondition(ip == net::ipv4_address::parse("127.0.0.1"));
  assert_precondition(ip.is_loopback());

  auto dt = deadline_timer(3s);
  auto et = elapsed_timer(deferred);
  assert_precondition(et.elapsed() == 0ms);
  et.start();
  assert_precondition(not et.is_deferred());

  assert_precondition(et.has_expired(0ms));
  std::this_thread::sleep_for(2s);
  assert_precondition(et.elapsed() >= 2s);
  fmt::println("elapsed: {:%S}s", et.elapsed());
  fmt::println("dt: elapsed/remaining: {:%S}s/{:%S}s", dt.elapsed(), dt.remaining());
  fmt::println("dt: expired={}", dt.has_expired());
  dt -= 1s;
  fmt::println("dt: elapsed/remaining: {:%S}s/{:%S}s", dt.elapsed(), dt.remaining());
  fmt::println("dt: expired={}", dt.has_expired());

  return 0;
}
