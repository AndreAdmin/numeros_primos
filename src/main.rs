fn main ()
{
    let mut i: u64 = 1;
    let mut j: u64 = 1;
    let mut contador: u8 = 0;
    
    loop
    {
        i += 1;

        while j <= i 
        {
            if i % j == 0 && contador <= 2
            {
                contador += 1;
            }

            if contador > 2
            {
                break
            }

            j += 1;
        }

        if contador == 2
        {
            println!("{}", i);
        }
        contador = 0;
        j = 1;

        if i == 18446744073709551615 // o maior numero q podemos calcular
        {
            break
        }
    }
}