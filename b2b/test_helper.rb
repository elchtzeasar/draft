require 'rubygems'

require 'test/unit'
require 'shoulda'


def assert_includes(substring, app, message=nil)
  app.wait_for_log(substring)
  full_message = build_message(message, "The following log (from <?>):\n#{app.read}\nwas expected to contain\n<?>.\n", app.name, substring)
  assert_block(full_message) { app.read.include? substring }
end

def assert_message_sent(messageName, app, message=nil)
  app.wait_for_log(messageName)
  full_message = build_message(message, "The following log (from <?>):\n#{app.read}\nwas expected to contain the message\n<?>.\n", app.name, messageName)
  assert_block(full_message) { app.read[/Message sent:.*#{messageName}/] }
end

def assert_does_not_include(substring, app, message=nil)
  app.wait_for_log(substring)
  full_message = build_message(message, "The following log (from <?>):\n#{app.read}\nwas expected to not contain\n<?>.\n", app.name, substring)
  assert_block(full_message) { !app.read.include? substring }
end

def assert_state_change(new_state, app, message=nil)
  full_message = build_message(message, "The following log (from <?>):\n#{app.read}\nwas expected to contain transition to\n<?>.\n", app.name, new_state)
  assert_block(full_message) { app.wait_for_state_change(new_state) }
end
