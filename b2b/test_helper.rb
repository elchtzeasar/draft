require 'rubygems'

require 'test/unit'
require 'shoulda'


def assert_includes(substring, app, message=nil)
  app.wait_for_log(substring)
  full_message = build_message(message, "<?> was expected to contain\n<?>.\n", app.read, substring)
  assert_block(full_message) { app.read.include? substring }
end
