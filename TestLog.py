import Log
import Entity


def main():
    e = Entity.Entity("1.2.3.4", "AA:AA:AA:AA:AA:AA")
    l = Log.Log("checkaaa.txt")
    
    for i in range (0, 10):
        l.add_block_record(e, i)


if __name__ == "__main__":
    main()