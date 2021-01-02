import SnifferToCsv
import SnifferToSqlite

def main():
    """
    """
    try:
        choice = int(input("choose 1 or 2 (CSV or Sqlite): "))
    except Exception:
        print("Invalid input, Csv was chosen by default")
        choice = 1

    if choice == 1:
        mySniffer = SnifferToCsv.Sniffer()
    elif choice == 2:
        mySniffer = SnifferToSqlite.Sniffer()
    else:
        print("Invalid input, Csv was chosen by default")
        mySniffer = SnifferToCsv.Sniffer()
        
    mySniffer.start_sniffing()




if __name__ == "__main__":
    main()