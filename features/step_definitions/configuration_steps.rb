Given /^I start the application$/ do
  @applications[:configuration].close unless @applications[:configuration].nil?
  @applications[:configuration] = DraftApp.new('default name', @current_scenario.name)
end

When /^I set the name to "([^"]*)"$/ do |name|
  @applications[:configuration].set_name name
end

Then /^the application should have name "([^"]*)"$/ do |name|
  @applications[:configuration].get_name.should == name
end

When /^I stop the application$/ do
  @applications[:configuration].close
  @applications[:configuration] = nil
end

