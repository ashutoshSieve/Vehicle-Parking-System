# SEQUENCE Diagram of PARK

```mermaid
sequenceDiagram
    autonumber
    participant Main
    participant Lot as ParkingLot
    participant Q as Slot Queue
    participant Slot as ParkSlot
    participant T as Ticket
    Main->>Lot: park(v, entryTime)
    Lot->>Q: pop suitable slot
    alt available
        Q-->>Lot: Slot*
        Lot->>Slot: occupy()
        Lot->>T: new Ticket(id, entry, Slot, v)
        Lot-->>Main: Ticket*
    else not available
        Lot-->>Main: nullptr
    end