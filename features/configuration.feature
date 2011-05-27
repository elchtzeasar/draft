Feature: Configuration
    In order to keep track of players configuration
    The configuration should to be read from file during startup and saved to file when closing

  @wip    
  Scenario: Setting configuration
    Given I start the application
     When I set the name to "new name"
     Then the application should have name "new name"

  @wip    
  Scenario: Reloading program after setting configuration
    Given I start the application
     When I set the name to "new name"
      And I stop the application
      And I start the application
     Then the application should have name "new name"