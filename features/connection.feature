Feature: Connecting clients
    In order to connect verify connection that clients can connect to a server
    Users should be able to connect to a hosted game

  Scenario: Old school one client one server
    Given I have started an application with the user "server"
      And I have started an application with the user "client" 
     When "server" hosts a game
      And "client" connects
     Then "server" should see "client connected"
      And "client" should see "Connected to server"

  @wip
  Scenario: Connect one client to a server
    Given I have started an application with the user "server"
      And I have started an application with the user "client" 
     When "server" hosts a game
      And "client" connects
     Then "server" should see "client connected"
      And "client" should see "server connected"

  @wip
  Scenario: Connect two clients to a server
    Given I have started an application with the user "server"
      And I have started an application with the user "first client" 
      And I have started an application with the user "second client" 
     When "server" hosts a game
      And "first client" connects
      And "second client" connects
     Then "server" should see "Connected to first client"
      And "server" should see "Connected to second client"
      And "first client" should see "Connected to server"
      And "first client" should see "Connected to second client"
      And "second client" should see "Connected to server"
      And "second client" should see "Connected to first client"