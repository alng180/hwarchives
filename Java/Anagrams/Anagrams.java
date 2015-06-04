import java.util.*;

// Anagram class is responsible for two primary functions for the whole Anagram program.
// First function is to accept a dictionary and a phrase and then filter out all of the words in the dictionary that 
// has any possibility of being a part of an anagram of that phrase
// Second function is to use recursion to find out all the possible anagrams using the given phrase and
// the words in the filtered dictionary. If a possible anagram is found, then the whole anagram is printed out.

public class Anagrams {
	
	private Set<String> dictionary;			// copy of the dictionary that is passed in	
//	private Set<String> set;				// copy of the filtered dictionary with the "legal"/possible words
	
	// Constructor for the Anagrams class
	// Takes in an initial full dictionary and saves a copy of it in this class
	//
	// @param dict	the full dictionary that is passed in through AnagramMain
	
	// @throws		IllegalArgumentException if dict is null
	
	// PRECONDITION: Dictionary contains at least one or more words and is not null
	// POSTCONDITION: A copy of the dictionary (dict) that was passed in is saved to the private variable dictionary
	public Anagrams(Set<String> dict) {
		// Precondition Check
		if (dict == null) {
			throw new IllegalArgumentException("Dictionary is null!");
		} else {
			dictionary = dict;	// save a copy of the full dictionary that is passed in
		}
	}
	
	// Filters out the full dictionary of the words that cannot be used in an Anagram
	// Saved the legal/possible words into a separate set of strings, which is returned
	// i.e. if the word to be scrambled is jack, the word bob would be filtered out, as there is no possible
	// way bob could be part of an anagram of jack
	
	// @param phrase	the phrase to be scrambled up and anagrams to be constructed for
	
	// @throws			IllegalArgumentException if the phrase is null
	
	// PRECONDITION: phrase is not null
	// POSTCONDITION: a Set<String> of possible/legal words is returned
	public Set<String> getWords(String phrase) {
		// Precondition check
		if (phrase == null) {
			throw new IllegalArgumentException("No phrase to scramble!");
		} else {
			// create a set that will contain all of the possible/legal words
			Set<String> legalwords = new TreeSet<String>();
			// convert the phrase into a LetterInventory of the phrase
			LetterInventory li = new LetterInventory(phrase);
			// for each word in the dictionary
			for (String word : dictionary) {
				// check if the word could possibly be a part of an anagram of phrase or not
				if (li.contains(word)) {
					// if so add it to legalwords
					legalwords.add(word);
				}
			}
			return legalwords;	// return the set of possible words
		}
	}
	
	// Print method for when no maximum number of words is specified
	// Determines the maximum possible number of words the phrase could be scrambled into
	// then passes it into the second print method that accepts a maximum as a variable
	
	// @param phrase	the phrase to be scrambled up and anagrams to be constructed for
	
	// @throws			IllegalArgumentException if the phrase is null
	
	// PRECONDITION: phrase is not null
	// POSTCONDITION: a second print method is called, passing in the newly calculated max value
	public void print(String phrase) {
		// precondition check
		if (phrase == null) {
			throw new IllegalArgumentException("No Phrase!");
		} else {
			// maximum possible words that could make up an anagram of phrase would be about equal
			// to the number of letters that make up phrase, as a letter is the smallest word possible
			int max = phrase.length();
			// call the second print method with the new max value
			print(phrase, max);
		}
	}
	
	// Primary print method
	// Initializes and sets up all the necessary variables/collections/etc to begin the recursion
	
	// @param phrase	the phrase to be scrambled up and anagrams to be constructed for
	// @param max		the numbers of words max that an anagram can use
	
	// @throws			IllegalArgumentException if the phrase is null
	// @throws			IllegalArgumentException if max is less than zero
	
	// PRECONDITION: phrase is not null and max > 0
	// POSTCONDITION: the solve method (private recursive method) is called and the recursion begins
	public void print(String phrase, int max) {
		// precondition checks
		if (phrase == null) {
			throw new IllegalArgumentException("No Phrase!");
		} else if (max < 0) {
			throw new IllegalArgumentException("Max Number of Words is Less Than Zero!");
		}
		// convert phrase into a LetterInventory
		LetterInventory ti = new LetterInventory(phrase);
		// obtain a set of the possible words that could make up an anagram of phrase
		Set<String> set = getWords(phrase);
		// create a list to save the answer/current anagram
		ArrayList<String> words = new ArrayList<String>();
		// call recursive method
		solve(ti, max, set, words);
	}
	
	// private method that does all of the recursion in order to solve/find all of the possible anagrams of phrase
	
	// @param ti		a LetterInventory of the phrase being scrambled
	// @param max		the numbers of words max that an anagram can use
	// @param set		the set of legal words that could be a part of an anagram of the phrase
	// @param words		the list that contains the current anagram/combination
	
	// PRECONDITION: max > 0, set is not null
	// POSTCONDITION: all legal anagrams of the phrase have been determined and printed out
	private void solve(LetterInventory ti, int max, Set<String> set, ArrayList<String> words) {
		// precondition check
		if (set == null) {
			throw new IllegalArgumentException();
		}
		// base case
		if (ti.size() == 0) {
			// if the size of the answer is less than or equal to max
			if (words.size() <= max) {				
				// print the answer out
				System.out.println(words.toString());
			}
		} else if (ti.size() < 0) {
		// else/recursive case
		} else {
			// for each word in the filtered dictionary
			for (String word: set) {
				String currentword = word;
				// if the letters of the current word can legally be contained in an anagram of phrase
				// or whatever is left of phrase
				if (ti.contains(currentword)) {
					// add word to the answer list and subtract letters of the current word from LetterInv
					words.add(currentword);
					ti.subtract(currentword);
					
					// recurse
					solve(ti,max,set,words);
					
					// backtrack
					words.remove(currentword);
					ti.add(currentword);
					}
				}
			}
		}
}