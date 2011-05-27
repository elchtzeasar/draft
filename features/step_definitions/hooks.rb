Before do |scenario|
  @current_scenario = scenario

  check_instances('before')

  @applications = {}
end

After do
  for user_name, draft_app in @applications do
    draft_app.close
  end unless @applications.nil?
  check_instances('after')
end

def check_instances(time_description)
  if `pgrep console_draft`.split("\n").size > 0
    puts "Found console_draft instances #{time_description} starting. This is bad!"
  end
end