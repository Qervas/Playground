use std::cmp::Ordering;
use std::io;
use std::process::exit;
use rand::Rng;

fn main() {
    println!("Guess the number!");

    let secret_number = rand::thread_rng().gen_range(1..101);
    // if cfg!(debug_assertions){
    //     println!("The secret number is: {}", secret_number);
    // }

    loop {
        println!("Please input your guess.");

        let mut guess  = String::new();
        io::stdin().read_line(&mut guess)
            .expect("Failed to read line");

        println!("You guessed: {guess}");

        let guess: u32 = match guess.trim().parse(){
            Ok(num) => num,
            Err(_) =>{ println!("Invalid input, number only");continue}
        };


        match guess.cmp(&secret_number){
            Ordering::Less => {println!("Maybe bigger?");}
            Ordering::Equal => {println!("You win!"); break;}
            Ordering::Greater => {println!("Maybe smaller?");}
        };
    }


    exit(0);
}
