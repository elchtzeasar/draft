require 'rubygems'

require 'test/unit'
require 'shoulda'


def assert_includes(substring, app, message=nil)
  app.wait_for_log(substring)
  full_message = build_message(message, "<?> was expected to contain\n<?>.\n", app.read, substring)
  assert_block(full_message) { app.read.include? substring }
end

def assert_state_change(new_state, app, message=nil)
  full_message = build_message(message, "<?> was expected to contain transition to\n<?>.\n", app.read, new_state)
  assert_block(full_message) { app.wait_for_state_change(new_state) }
end
