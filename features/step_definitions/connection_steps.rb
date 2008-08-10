require 'features/test_helper'

require 'draft_app'

Before do
  @applications = {}
end

Given /^I have started an application with the user "([^"]*)"$/ do |username|
  @applications[username] = DraftApp.new(username, @current_scenario.name)
  @applications[username].configure_name
end

When /^"([^"]*)" hosts a game$/ do |username|
  @applications[username].host
end

When /^"([^"]*)" connects$/ do |username|
  @applications[username].connect
end

Then /^"([^"]*)" should see "([^"]*)"$/ do |username, expected_log|
  @applications[username].wait_for_log(expected_log).should include expected_log
end
