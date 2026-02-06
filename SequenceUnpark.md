# SEQUENCE Diagram of UNPARK

```mermaid
sequenceDiagram
    autonumber
    participant Main
    participant Lot as ParkingLot
    participant T as Ticket
    participant FC as FeeCalculator
    participant R as Receipt
    participant Slot as ParkSlot

    Main->>Lot: unpark(ticketId, exitTime)
    Lot->>T: find ticket by id
    Lot->>FC: calculateFee(entry, exitTime)
    FC-->>Lot: amount
    Lot->>R: write_receipt(T, amount, exitTime)
    Lot->>Slot: free()
    Lot->>Lot: return slot to queue
    Lot->>T: delete ticket
    Lot-->>Main: amount