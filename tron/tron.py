# TODO: voltar para si mesmo
import pygame
import tron_engine

pygame.init()

res = width, height = (1000, 700)
black = (0, 0, 0)
white = (255, 255, 255)
red = (255, 0, 0)
clock = pygame.time.Clock()
size = 10
FPS = 25
screen = pygame.display.set_mode(res)
pygame.display.set_caption('Tron')


def message(msg, color, h):
    screen_text = pygame.font.SysFont(None, 25).render(msg, True, color)
    screen.blit(screen_text, [width/2 - screen_text.get_width()/2, h])


def over(gameExit, gameOver, winner):
    screen.fill(black)
    message(winner + " wins!", white, height/4)
    message("Game Over, press A to play again or Q to quit", white, height/2)
    pygame.display.update()

    # listen for action
    for event in pygame.event.get():
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_q:
                gameExit = True
                gameOver = False
            elif event.key == pygame.K_a:
                gameLoop()

    return gameExit, gameOver


def gameLoop():
    position = [width/4, height/2]
    player = tron_engine.Player("player 1", "white_tron.png", screen, res, position, white, size, [0, 0])
    player.init("right")

    position2 = [3*width/4, height/2]
    computer = tron_engine.Player("computer", "red_tron.png", screen, res, position2, red, size, [0, 0])
    computer.init("left")

    gameExit = False
    gameOver = False
    winner = None

    while not gameExit:
        while gameOver:
            player.init("right")
            computer.init("left")
            gameExit, gameOver = over(gameExit, gameOver, winner)

        # events
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                gameExit = True
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_LEFT:
                    player.change_direction("left")
                elif event.key == pygame.K_RIGHT:
                    player.change_direction("right")
                elif event.key == pygame.K_UP:
                    player.change_direction("up")
                elif event.key == pygame.K_DOWN:
                    player.change_direction("down")

        # logic
        player.move()
        computer.random_move([player.path, computer.path])
        if player.collision() or player.collision_with_path([player.path, computer.path]):
            gameOver = True
            winner = computer.name
        if computer.collision() or computer.collision_with_path([computer.path, player.path]):
            gameOver = True
            winner = player.name

        # display
        screen.fill(black)
        player.drawplayer()
        computer.drawplayer()
        pygame.display.update()

        # fps
        clock.tick(FPS)

    pygame.quit()
    quit()

gameLoop()
